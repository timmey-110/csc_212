import subprocess
import unittest
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Iterable, Optional

from gradescope_utils.autograder_utils.decorators import weight


@dataclass
class CommandOutput:
    stdout: str
    stderr: str
    exit_code: int
    timeout: bool


def run(cmd: Iterable[Any], timeout: Optional[int] = 5) -> CommandOutput:
    cmd = " ".join(str(x) for x in cmd)
    try:
        proc = subprocess.run(
            cmd, shell=True, capture_output=True, text=True, timeout=timeout
        )
        return CommandOutput(
            stdout=proc.stdout,
            stderr=proc.stderr,
            exit_code=proc.returncode,
            timeout=False,
        )
    except subprocess.TimeoutExpired:
        return CommandOutput(stdout="", stderr="", exit_code=-1, timeout=True)


def build(cpp_path: Path, executable_path: Path) -> CommandOutput:
    gcc_flags = [
        "-std=c++17",
        "-g",
        "-O0",
        "-Wall",
        "-Wextra",
        "-Wpedantic",
        "-Werror",
        "-fsanitize=address,undefined",
        "-fstack-protector-strong",
        "-D_GLIBCXX_DEBUG",
    ]
    cmd = ["g++", *gcc_flags, "-o", executable_path.as_posix(), cpp_path.as_posix()]
    return run(cmd, timeout=None)


class TestAll(unittest.TestCase):
    def assert_cpp_ok(self, cpp_name: str) -> None:
        autograder_path = Path("/autograder/source")
        submission_path = Path("/autograder/submission")

        # Ensure catch2 is available.
        catch2_path = autograder_path / "catch.hpp"
        submission_catch2_path = submission_path / "catch.hpp"
        submission_catch2_path.write_bytes(catch2_path.read_bytes())

        cpp_path = submission_path / cpp_name

        executable_path = cpp_path.with_suffix("")
        executable_name = executable_path.name

        if not cpp_path.is_file():
            self.fail(
                "\n".join(
                    [
                        "",
                        "ERROR".center(80, "*"),
                        f"\n{cpp_path} does not exist",
                    ]
                )
            )

        output = build(cpp_path, executable_path)

        if output.timeout:
            self.fail(
                "\n".join(
                    [
                        "",
                        "ERROR".center(80, "*"),
                        f"\nTime limit exceeded when compiling {cpp_name}",
                    ]
                )
            )

        if output.exit_code != 0:
            self.fail(
                "\n".join(
                    [
                        "",
                        "ERROR".center(80, "*"),
                        f"Compilation of {cpp_name} failed with exit code {output.exit_code}",
                        "STDOUT".center(80, "*"),
                        output.stdout,
                        "STDERR".center(80, "*"),
                        output.stderr,
                    ]
                )
            )

        output = run([executable_path.absolute().as_posix()])

        if output.timeout:
            self.fail(
                "\n".join(
                    [
                        "",
                        "ERROR".center(80, "*"),
                        f"\nTime limit exceeded when running {executable_name}",
                    ]
                )
            )

        if output.exit_code != 0:
            self.fail(
                "\n".join(
                    [
                        "",
                        "ERROR".center(80, "*"),
                        f"Running {executable_name} failed with exit code {output.exit_code}",
                        "STDOUT".center(80, "*"),
                        output.stdout,
                        "STDERR".center(80, "*"),
                        output.stderr,
                    ]
                )
            )

    @weight(1)
    def test_submitted(self):
        pass

    @weight(10)
    def test_pointers(self):
        self.assert_cpp_ok("pointers.cpp")

    @weight(15)
    def test_cstyle_arrays(self):
        self.assert_cpp_ok("cstyle_arrays.cpp")

    @weight(15)
    def test_reverse(self):
        self.assert_cpp_ok("reverse.cpp")

    @weight(15)
    def test_permute(self):
        self.assert_cpp_ok("permute.cpp")

    @weight(15)
    def test_allocate(self):
        self.assert_cpp_ok("allocate.cpp")

    @weight(15)
    def test_array(self):
        self.assert_cpp_ok("array.cpp")

    @weight(30)
    def test_matrix(self):
        self.assert_cpp_ok("matrix.cpp")

    @weight(100)
    def test_tensor(self):
        self.assert_cpp_ok("tensor.cpp")

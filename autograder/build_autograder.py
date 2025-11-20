from __future__ import annotations

import argparse
import json
import shutil
import subprocess
from dataclasses import dataclass, field
from pathlib import Path
from typing import Iterable, Optional, Sequence


@dataclass
class Unit:
    name: str
    requirements: Sequence[str] = field(default_factory=list)
    dependencies: Sequence[str] = field(default_factory=list)
    analysis: Optional[str] = None

    def tests(self: Unit) -> Iterable[str]:
        cpp_requirements = [
            requirement
            for requirement in self.requirements
            if requirement.endswith(".cpp")
        ]
        cpp_dependencies = [
            dependency
            for dependency in self.dependencies
            if dependency.endswith(".cpp")
        ]

        has_executable = len(self.requirements) > 0
        has_analysis = self.analysis is not None

        if has_executable:
            yield "\n".join(
                (
                    "@weight(1)",
                    f"def test_{self.name}(self) -> None:",
                    f"\trequirements = {self.requirements}",
                    f"\tdependencies = {self.dependencies}",
                    f"\texecutable_name = 'test_{self.name}'",
                    f"\tcpp_files = {cpp_requirements + cpp_dependencies}",
                    "\tself.assert_exists(requirements)",
                    "\tself.assert_exists(dependencies)",
                    "\tself.assert_cpp_tests(cpp_files, executable_name)",
                )
            )

        if has_analysis:
            buf = [
                "@weight(1)",
                f"def test_{self.name}_analysis(self) -> None:",
                f"\tanalysis = '{self.analysis}'",
            ]
            if has_executable:
                buf.append(f"\tself.test_{self.name}()")
            buf.append("\tself.assert_analysis_tests(analysis)")
            yield "\n".join(buf)


def generate_test_all(units: Iterable[Unit]) -> str:
    buf = [
        "from autograder_base import AutograderBase",
        "",
        "from gradescope_utils.autograder_utils.decorators import weight",
        "",
        "",
        "class TestAll(AutograderBase):",
        "\t@weight(1)",
        "\tdef test_submission(self) -> None:",
        "\t\tpass",
        "",
    ]
    for unit in units:
        for test in unit.tests():
            buf.extend("\t" + l for l in test.splitlines())
            buf.append("")
    return "\n".join(buf)


def generate_build_autograder_zip(units: Iterable[Unit]) -> str:
    buf = [
        "#!/bin/bash",
        "",
        "rm -rf ./submission/ ./autograder.zip",
        "mkdir -p ./submission/",
    ]

    for unit in units:
        for dependency in unit.dependencies:
            buf.append(f"cp ../handout/{dependency} ./submission/")

    buf.extend(["zip -r autograder.zip .", "rm -rf ./submission/"])

    return "\n".join(buf)


def load_units(json_str: str) -> Iterable[Unit]:
    d = json.loads(json_str)
    for v in d:
        yield Unit(**v)


def get_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser()
    parser.add_argument("lab_path", type=Path)
    return parser


def main() -> None:
    base_autograder_path = Path("./autograder/")

    parser = get_parser()
    args = parser.parse_args()

    lab_path = args.lab_path
    autograder_path = lab_path / "autograder"
    spec_path = autograder_path / "spec.json"
    handout_path = lab_path / "handout"

    assert (
        lab_path.exists()
        and autograder_path.exists()
        and spec_path.exists()
        and handout_path.exists()
    )

    units = list(load_units(spec_path.read_text()))
    test_all_str = generate_test_all(units)
    build_autograder_zip_str = generate_build_autograder_zip(units)

    shutil.copytree(
        base_autograder_path,
        autograder_path,
        dirs_exist_ok=True,
    )

    test_all_path = autograder_path / "tests" / "test_all.py"
    test_all_path.write_text(test_all_str)

    build_autograder_zip_path = autograder_path / "build_autograder_zip.sh"
    build_autograder_zip_path.write_text(build_autograder_zip_str)

    subprocess.run(
        ["chmod +x ./build_autograder_zip.sh; ./build_autograder_zip.sh"],
        shell=True,
        cwd=autograder_path,
    )


if __name__ == "__main__":
    main()

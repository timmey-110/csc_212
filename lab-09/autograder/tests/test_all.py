from autograder_base import AutograderBase

from gradescope_utils.autograder_utils.decorators import weight


class TestAll(AutograderBase):
	@weight(1)
	def test_submission(self) -> None:
		pass
	@weight(1)
	def test_set(self) -> None:
		requirements = ['set.h', 'set.cpp']
		dependencies = ['test_set.cpp', 'doctest.h']
		executable_name = 'test_set'
		cpp_files = ['set.cpp', 'test_set.cpp']
		self.assert_exists(requirements)
		self.assert_exists(dependencies)
		self.assert_cpp_tests(cpp_files, executable_name)

	def test_set_analysis(self) -> None:
		analysis = 'set.md'
		self.test_set()
		self.assert_analysis_tests(analysis)

	@weight(1)
	def test_map(self) -> None:
		requirements = ['map.h', 'map.cpp']
		dependencies = ['test_map.cpp', 'doctest.h']
		executable_name = 'test_map'
		cpp_files = ['map.cpp', 'test_map.cpp']
		self.assert_exists(requirements)
		self.assert_exists(dependencies)
		self.assert_cpp_tests(cpp_files, executable_name)

	def test_map_analysis(self) -> None:
		analysis = 'map.md'
		self.test_map()
		self.assert_analysis_tests(analysis)

	@weight(1)
	def test_sequence(self) -> None:
		requirements = ['sequence.h', 'sequence.cpp']
		dependencies = ['test_sequence.cpp', 'doctest.h']
		executable_name = 'test_sequence'
		cpp_files = ['sequence.cpp', 'test_sequence.cpp']
		self.assert_exists(requirements)
		self.assert_exists(dependencies)
		self.assert_cpp_tests(cpp_files, executable_name)

	def test_sequence_analysis(self) -> None:
		analysis = 'sequence.md'
		self.test_sequence()
		self.assert_analysis_tests(analysis)

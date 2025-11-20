from autograder_base import AutograderBase

from gradescope_utils.autograder_utils.decorators import weight


class TestAll(AutograderBase):
	@weight(1)
	def test_submission(self) -> None:
		pass

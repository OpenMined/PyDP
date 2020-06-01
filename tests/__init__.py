import unittest
import pycodestyle


class TestCodeFormat(unittest.TestCase):
    def test_conformance(self):
        """Test that we conform to PEP-8."""
        style = pycodestyle.StyleGuide(quiet=True)
        # style.
        style.input_dir("algorithms")
        style.input_dir("base")
        result = style.check_files()
        assert result.total_errors == 0

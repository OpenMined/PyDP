import unittest
import pycodestyle


class TestCodeFormat(unittest.TestCase):

    def test_conformance(self):
        """Test that we conform to PEP-8."""
        style = pycodestyle.StyleGuide(quiet=True)
        # style.
        result = style.check_files(['*.py'])
        self.assertEqual(result.total_errors, 0,
                         "Found code style errors (and warnings).")

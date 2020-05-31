import pytest
import pydp as dp


class TestLogging:
    def test_logging(self):
        directory = "tests"
        vlog_level = 3
        tl = dp.Logging(directory, "log_test", vlog_level)
        assert tl.log_status is True

    def test_logging1(self):
        directory = ""
        vlog_level = 3
        tl1 = dp.Logging(directory, "log_test.txt", vlog_level)
        assert tl1.log_status is False

    def test_logging2(self):
        directory = "tests"
        vlog_level = 3
        tl2 = dp.Logging(directory, "", vlog_level)
        assert tl2.log_status is False

    def test_vlog_level(self):
        directory = "tests"
        vlog_level = 1
        tvl = dp.Logging(directory, "log_test.txt", vlog_level)
        assert tvl.vlog_level == vlog_level

    def test_vlog_directory(self):
        directory = "tests"
        vlog_level = 1
        tvd = dp.Logging(directory, "log_test.txt", vlog_level)
        assert tvd.log_directory == "tests/"

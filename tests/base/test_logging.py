import pytest
import pydp as dp

# TODO
# class TestLogging:
#     def test_logging(self):
#         directory = "tests"
#         vlog_level = 3
#         success = dp.Logging(directory, "log_test", vlog_level)
#         assert success is True

#     def test_logging1(self):
#         directory = ""
#         vlog_level = 3
#         success = dp.Logging(directory, "log_test.txt", vlog_level)
#         assert success is False

#     def test_logging2(self):
#         directory = "tests"
#         vlog_level = 3
#         success = dp.Logging(directory, "", vlog_level)
#         assert success is False

#     def test_vlog_level(self):
#         directory = "tests"
#         vlog_level = 1
#         success = dp.Logging(directory, "log_test.txt", vlog_level)
#         assert dp.Logging.vlog_level == vlog_level

#     def test_vlog_directory(self):
#         directory = "tests"
#         vlog_level = 1
#         success = dp.logging.init_logging(directory, "log_test.txt", vlog_level)
#         assert dp.Logging.log_directory == "tests/"

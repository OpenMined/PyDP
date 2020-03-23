import pytest

import pydp as pd
# Creating a Class TestLogging
class TestLogging():
    #Creating First testcase
    def test_logging(self):
        directory = 'tests'
        vlog_level = 3
        l = pd.logging.init_logging(directory, 'log_test', vlog_level)
        #if both directory and vlog_level contains value the test will be pass
        assert l == True

    def test_logging1(self):
        directory = ''
        vlog_level = 3
        l = pd.logging.init_logging(directory, 'log_test.txt', vlog_level)
        #location of directory must be given otherwise test will fail
        assert l == False

    def test_logging2(self):
        directory = 'tests'
        vlog_level = 3
        l = pd.logging.init_logging(directory, '', vlog_level)
        #All the attributes of init_logging must be given otherwise test will fail
        assert l == False

    # Creating an instance which will return level of vlog
    def test_vlog_level(self):
        directory = 'tests'
        vlog_level = 1
        l = pd.logging.init_logging(directory, 'log_test.txt', vlog_level)
        #outcome must be equal to vlog_level otherwise the code will fail
        assert pd.logging.get_vlog_level() == vlog_level

    # Creating an Instance which will return the test_vlog_directory
    def test_vlog_directory(self):
        directory = 'tests'
        vlog_level = 1
        l = pd.logging.init_logging(directory, 'log_test.txt', vlog_level)
        #outcome must be location of directory otherwise test will fail
        assert pd.logging.get_log_directory() == 'tests/'

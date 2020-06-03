import pytest
import pydp as dp

def test_mean ():
    a = [1,2,4,6.0,8]
    assert dp.util.mean(a) == 4.2
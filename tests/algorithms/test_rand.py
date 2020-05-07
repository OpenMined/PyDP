import pytest
import pydp as dp


def test_rand_UniformDouble():
    ud = dp.UniformDouble()
    assert isinstance(ud, float)
    assert 0 <= ud < 1


def test_rand_Geometric():
    gn = dp.Geometric()
    assert isinstance(gn, int)
    assert 0 <= gn <= 1025

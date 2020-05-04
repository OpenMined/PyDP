import pytest
import pydp as dp


def test_algorithms_BoundedMean():
    bm1 = dp.BoundedMean(3.4, 1, 2)
    assert (bm1, dp.BoundedMean)
    assert isinstance(bm1.result([1.5, 2, 2.5]), float)

    bm2 = dp.BoundedMean(3.4)
    assert isinstance(bm2, dp.BoundedMean)
    assert isinstance(bm2.result([1.5, 2, 2.5]), float)

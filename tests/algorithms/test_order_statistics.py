import pytest

# verify with actual value
import statistics
import math

import pydp as dp


@pytest.fixture
def data():
    kDataSize = 10000
    a = []
    for i in range(kDataSize):
        a.append(200 * i / kDataSize)
    return a


def test_max(data):
    maxx = dp.Max(1.0, 0, 2048)
    assert 190 < maxx.result(data, 1.0) < 210

    assert max(data) - 10 < maxx.result(data, 1.0) < max(data) + 10


def test_min(data):
    maxx = dp.Min(1.0, 0, 2048)

    assert min(data) - 10 < maxx.result(data, 1.0) < min(data) + 10

    assert -10 < maxx.result(data, 1.0) < 10


def test_median(data):
    maxx = dp.Median(1.0, 0, 2048)

    assert (
        statistics.median(data) - 20
        < maxx.result(data, 1.0)
        < statistics.median(data) + 20
    )

    assert 90 <= maxx.result(data, 1.0) <= 100


def test_median1(data):
    maxx = dp.Median(1.0)
    assert (
        statistics.median(data) - 20
        < maxx.result(data, 1.0)
        < statistics.median(data) + 20
    )
    assert 90 <= maxx.result(data, 1.0) <= 100


def percentile(N, percent, key=lambda x: x):
    """
    Find the percentile of a list of values.

    @parameter N - is a list of values. Note N MUST BE already sorted.
    @parameter percent - a float value from 0.0 to 1.0.
    @parameter key - optional key function to compute value from each element of N.

    @return - the percentile of the values
    """
    if not N:
        return None
    k = (len(N) - 1) * percent
    f = math.floor(k)
    c = math.ceil(k)
    if f == c:
        return key(N[int(k)])
    d0 = key(N[int(f)]) * (c - k)
    d1 = key(N[int(c)]) * (k - f)
    return d0 + d1


def test_percentile(data):
    maxx = dp.Percentile(1.0, 0, 2048)
    maxx.percentile = 0.45

    actual_percentile = int(percentile(data, 0.45))

    assert maxx.percentile == 0.45
    assert actual_percentile - 10 < maxx.result(data, 1.0) < actual_percentile + 10
    assert 80 < maxx.result(data, 1.0) < 100


# TODO Yet some more tests

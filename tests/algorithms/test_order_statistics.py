# stdlib
import math

# verify with actual value
import statistics

# third party
from conftest import expect_near
from conftest import percentile
import pytest

# pydp absolute
import pydp as dp

kDataSize = 10000
data_floats = [200.0 * i / kDataSize for i in range(kDataSize)]
data_ints = [int(200 * i / kDataSize) for i in range(kDataSize)]
type_data_algorithm = [
    ("int", data_ints, dp.algorithms.laplacian.Max),
    ("float", data_floats, dp.algorithms.laplacian.Max),
    ("int", data_ints, dp.algorithms.laplacian.Min),
    ("float", data_floats, dp.algorithms.laplacian.Min),
    ("int", data_ints, dp.algorithms.laplacian.Median),
    ("float", data_floats, dp.algorithms.laplacian.Median),
]

# NOTE: One needs to use https://pypi.org/project/pytest-lazy-fixture/ to have fixtues in parameters.
# Using none fixtured data instead of adding a pytest-lazy-fixture.
@pytest.mark.parametrize("dtype, data", [("int", data_ints), ("float", data_floats)])
def test_min(data, dtype):

    minn = dp.algorithms.laplacian.Min(
        dtype=dtype, epsilon=1.0, lower_bound=0, upper_bound=200
    )
    assert expect_near(min(data), minn.quick_result(data), 10)
    assert expect_near(0, minn.quick_result(data), 10)


@pytest.mark.parametrize("dtype, data", [("int", data_ints), ("float", data_floats)])
def test_max(data, dtype):
    maxx = dp.algorithms.laplacian.Max(
        dtype=dtype, epsilon=1.0, lower_bound=0, upper_bound=200
    )
    assert 190 < maxx.quick_result(data) < 210

    assert expect_near(max(data), maxx.quick_result(data), 10)


@pytest.mark.parametrize("dtype, data", [("int", data_ints), ("float", data_floats)])
def test_median(data, dtype):

    median = dp.algorithms.laplacian.Median(
        dtype=dtype, epsilon=1.0, lower_bound=0, upper_bound=200
    )

    assert expect_near(statistics.median(data), median.quick_result(data), 20)


@pytest.mark.parametrize("dtype", ["int", "float"])
def test_percentile_getter(dtype):

    expected_percentile = 0.45

    dp_percentile = dp.algorithms.laplacian.Percentile(
        dtype=dtype,
        epsilon=1.0,
        percentile=expected_percentile,
        lower_bound=0,
        upper_bound=200,
    )
    assert dp_percentile.percentile == expected_percentile


@pytest.mark.parametrize("dtype, data, order_statistic", type_data_algorithm)
def test_order_statistic_datatypes(data, dtype, order_statistic):

    order_statistic_1 = order_statistic(dtype=dtype, epsilon=1.0)
    order_statistic_2 = order_statistic(
        dtype=dtype, epsilon=1.0, lower_bound=0, upper_bound=200
    )
    res = order_statistic_2.quick_result(data)

    assert isinstance(order_statistic_1, order_statistic)
    assert isinstance(order_statistic_2, order_statistic)

    assert isinstance(res, type(data[0]))


@pytest.mark.parametrize(
    "dtype, data, dp_percentile",
    [
        ("int", data_ints, dp.algorithms.laplacian.Percentile),
        ("float", data_floats, dp.algorithms.laplacian.Percentile),
    ],
)
def test_percentile_datatypes(data, dtype, dp_percentile):

    dp_percentile_2 = dp_percentile(
        dtype=dtype, epsilon=1.0, percentile=0.45, lower_bound=0, upper_bound=200
    )
    res = dp_percentile_2.quick_result(data)

    assert isinstance(dp_percentile_2, dp_percentile)

    assert isinstance(res, float)


# TODO Yet some more tests

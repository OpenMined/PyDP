import pytest
from pydp.distributions import (
    LaplaceDistribution,
    GaussianDistribution,
    # GeometricDistribution,
)
import pydp as dp
import math
from typing import List
from itertools import accumulate
import math


k_num_samples = 10000000
k_num_geometric_samples = 1000000
k_gaussian_samples = 1000000
k_one_over_log2 = 1.44269504089


def skew(samples: List[float], mu: float, sigma: float):
    """Unfortunately this is implemented in third_party/differential-privacy/cc/algorithms/distributions_test.cc
       and we don't want to pull the test files in. I'm assuming it'll be moved to
       third_party/differential-privacy/cc/algorithms/util.h If they (upstream) move it we can use it.
       Until then this should suffice. #FIXME: when possible we can fix this.
    """
    skew = list(
        accumulate(samples, lambda lhs, rhs: lhs + (rhs - mu) * (rhs - mu) * (rhs - mu))
    )[-1]
    return skew / (len(samples) * sigma * sigma * sigma)


def kurtosis(samples: List[float], mu: float, var: float):
    """Unfortunately this is implemented in third_party/differential-privacy/cc/algorithms/distributions_test.cc
       and we don't want to pull the test files in. I'm assuming it'll be moved to
       third_party/differential-privacy/cc/algorithms/util.h If they (upstream) move it we can use it.
       Until then this should suffice. #FIXME: when possible we can fix this.
    """
    kurt = list(
        accumulate(samples, lambda lhs, rhs: lhs + ((rhs - mu) * (rhs - mu)) ** 2)
    )[-1]
    n = len(samples)
    kurt = (n + 1) * kurt / (n * var * var)
    kurt -= 3 * (n - 1)
    kurt *= (n - 1) / (n - 2) / (n - 3)
    return kurt


# From what I understand @openmined/dp-research are going to look at validating correctness
# Until then we can use this to assert on floating point numbers.
# FIXME: When possible we should add 'correctness' tests.
expect_near = lambda expected, actual, tol: (
    expected + tol >= actual and expected - tol <= actual
)


class TestLaplaceDistribution:
    def test_diversity_getter(self):
        sensitivity, epsilon = 1.0, 22.0
        dist = LaplaceDistribution(epsilon=epsilon, sensitivity=sensitivity)
        assert dist.get_diversity() == sensitivity / epsilon

    def test_check_statistics_for_geo_unit_values(self):

        ld = LaplaceDistribution(epsilon=1.0, sensitivity=1.0)
        samples = [ld.sample(scale=1.0) for _ in range(k_num_geometric_samples)]
        mean = dp.util.mean(samples)
        var = dp.util.variance(samples)

        assert expect_near(0.0, mean, 0.01)
        assert expect_near(2.0, var, 0.1)
        assert expect_near(0.0, skew(samples, mean, math.sqrt(var)), 0.1)
        assert expect_near(3.0, kurtosis(samples, mean, var), 0.1)


class TestGaussianDistribution:
    def test_standard_deviation_getter(self):
        stddev = k_one_over_log2
        dist = GaussianDistribution(stddev)
        assert dist.stddev == stddev


class TestLaplaceDistributionDatatypes:
    def test_LaplaceDistributionTypes(self):
        ld = LaplaceDistribution(epsilon=1.0, sensitivity=1.0)
        assert isinstance(ld, LaplaceDistribution)

        sud = ld.get_uniform_double()
        assert isinstance(sud, float)
        lds = ld.sample()
        lds1 = ld.sample(4.0)
        assert isinstance(lds, float)
        assert isinstance(lds1, float)
        ldg = ld.get_diversity()
        assert isinstance(ldg, float)
        # TODO
        # lcdf = ld.cdf(2.0, 0.5)
        # assert isinstance(lcdf, float)


class TestGaussianDistributionDataTypes:
    def test_GaussianDistributionTypes(self):
        gd = GaussianDistribution(3)
        assert isinstance(gd, GaussianDistribution)

        gds = gd.sample()
        gds1 = gd.sample(1.0)
        assert isinstance(gds, float)
        assert isinstance(gds1, float)
        gdstd = gd.stddev
        assert isinstance(gdstd, float)


class TestGeometricDistribution:
    @pytest.mark.skip(reason="This test should pass, see comments")
    def test_ratios(self):
        """
        This test fails. It's a replica of
         https://github.com/google/differential-privacy/blob/9923ad4ee1b84a7002085e50345fcc05f2b21bcb/cc/algorithms/distributions_test.cc#L208 and should pass.
        """
        from collections import Counter

        p = 1e-2
        dist = GeometricDistribution(lambda_=-1.0 * math.log(1 - p))
        samples = [dist.sample() for _ in range(k_num_geometric_samples)]
        counts = list(Counter([s for s in samples if s < 51]).values())
        ratios = [c_i / c_j for c_i, c_j in zip(counts[:-1], counts[1:])]

        assert expect_near(p, dp.util.mean(ratios), p / 1e-2)


# TODO: port the following tests
#
# TEST(LaplaceDistributionTest, CheckStatisticsForUnitValues)
# TEST(LaplaceDistributionTest, CheckStatisticsForSpecificDistribution)
# TEST(LaplaceDistributionTest, CheckStatisticsForSpecificScaledDistribution)
# TEST(GaussDistributionTest, CheckStatisticsForUnitValues)
# TEST(GaussDistributionTest, CheckStatisticsForSpecificDistribution)
# TEST(GaussDistributionTest, CheckStatisticsForSpecificScaledDistribution)
#

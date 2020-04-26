import pytest
import pydp as dp
import math

kOneOverLog2 = 1.44269504089


class TestLaplaceDistribution:
    def test_diversity_getter(self):
        stddev = kOneOverLog2
        dist = dp.LaplaceDistribution(stddev)
        assert dist.GetDiversity() == stddev

    def test_cdf(self):
        assert dp.LaplaceDistribution.cdf(5, 0) == 0.5
        assert dp.LaplaceDistribution.cdf(1, -1) == 0.5 * math.exp(-1)
        assert dp.LaplaceDistribution.cdf(1, 1) == 1 - 0.5 * math.exp(-1)


class TestGaussianDistribution:
    def test_standard_deviation_getter(self):
        stddev = kOneOverLog2
        dist = dp.GaussianDistribution(stddev)
        assert dist.Stddev() == stddev


# TODO: port the following tests
#
# TEST(LaplaceDistributionTest, CheckStatisticsForUnitValues)
# TEST(LaplaceDistributionTest, CheckStatisticsForSpecificDistribution)
# TEST(LaplaceDistributionTest, CheckStatisticsForSpecificScaledDistribution)
# TEST(GaussDistributionTest, CheckStatisticsForUnitValues)
# TEST(GaussDistributionTest, CheckStatisticsForSpecificDistribution)
# TEST(GaussDistributionTest, CheckStatisticsForSpecificScaledDistribution)
#

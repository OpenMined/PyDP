import pytest
import pydp as dp
import math

kOneOverLog2 = 1.44269504089


# legacy tests
# no new tests exists for these that can be tested
# class TestLaplaceDistribution:
    # def test_diversity_getter(self):
    #     stddev = kOneOverLog2
    #     dist = dp.LaplaceDistribution(stddev, 1.0)
    #     assert dist.get_diversity() == stddev

    # def test_cdf(self):
    #     assert dp.LaplaceDistribution.cdf(5, 0) == 0.5
    #     assert dp.LaplaceDistribution.cdf(1, -1) == 0.5 * math.exp(-1)
    #     assert dp.LaplaceDistribution.cdf(1, 1) == 1 - 0.5 * math.exp(-1)


class TestGaussianDistribution:
    def test_standard_deviation_getter(self):
        stddev = kOneOverLog2
        dist = dp.GaussianDistribution(stddev)
        assert dist.stddev() == stddev


class TestLaplaceDistributionDatatypes:
    def test_LaplaceDistributionTypes(self):
        ld = dp.LaplaceDistribution(2.0, 1.0)
        assert isinstance(ld, dp.LaplaceDistribution)

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
        gd = dp.GaussianDistribution(3)
        assert isinstance(gd, dp.GaussianDistribution)

        gds = gd.sample()
        gds1 = gd.sample(1.0)
        assert isinstance(gds, float)
        assert isinstance(gds1, float)
        gdstd = gd.stddev()
        assert isinstance(gdstd, float)


# TODO: port the following tests
#
# TEST(LaplaceDistributionTest, CheckStatisticsForUnitValues)
# TEST(LaplaceDistributionTest, CheckStatisticsForSpecificDistribution)
# TEST(LaplaceDistributionTest, CheckStatisticsForSpecificScaledDistribution)
# TEST(GaussDistributionTest, CheckStatisticsForUnitValues)
# TEST(GaussDistributionTest, CheckStatisticsForSpecificDistribution)
# TEST(GaussDistributionTest, CheckStatisticsForSpecificScaledDistribution)
#

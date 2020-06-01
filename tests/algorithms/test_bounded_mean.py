import pytest
import pydp as dp


def test_c_api():
    a = [2, 4, 6, 8]

    mean_algorithm = dp.BoundedMean(1.0, 1, 9)
    assert 1.0 <= mean_algorithm.result(a) <= 9.0


def test_bounded_mean():
    bm1 = dp.BoundedMean(3.4, 1, 2)
    assert isinstance(bm1, dp.BoundedMean)
    assert isinstance(bm1.result([1.5, 2, 2.5]), float)

    bm2 = dp.BoundedMean(3.4)
    assert isinstance(bm2, dp.BoundedMean)
    # assert isinstance(bm2.result([1.5, 2, 2.5]), float)


# TODO: port this test
#
# TYPED_TEST(BoundedMeanTest, BasicTest) {
#   std::vector<TypeParam> a = {2, 4, 6, 8};
#   std::unique_ptr<BoundedMean<TypeParam>> mean =
#       typename BoundedMean<TypeParam>::Builder()
#           .SetEpsilon(1.0)
#           .SetLower(1)
#           .SetUpper(9)
#           .Build()
#           .ValueOrDie();
#   Output result = mean->Result(a.begin(), a.end()).ValueOrDie();
#   EXPECT_GE(GetValue<double>(result), 1);
#   EXPECT_LE(GetValue<double>(result), 9);
# }
#
# TODO: port remaining tests from the C++ library

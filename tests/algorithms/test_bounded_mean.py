import pytest
import pydp as dp


class TestBoundedMean():

    def test_basic(self):
        a = [2, 4, 6, 8]
        mean = dp.BoundedMeanInt.Builder().set_epsilon(1.0). \
               set_lower(1).set_upper(9).build().value_or_die()
        assert 1 < dp.get_value(mean.result(a).value_or_die()) < 9

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

import pytest
from pydp.algorithms.laplacian import BoundedMean

expect_near = lambda expected, actual, tol: (
    expected + tol >= actual and expected - tol <= actual
)


def test_python_api():
    a = [2, 4, 6, 8]

    mean_algorithm = BoundedMean(
        epsilon=1.0, lower_bound=1, upper_bound=9, dtype="float"
    )
    assert 1.0 <= mean_algorithm.quick_result(a) <= 9.0


def test_bounded_mean():
    bm1 = BoundedMean(epsilon=3.4, lower_bound=1, upper_bound=2, dtype="float")
    assert isinstance(bm1, BoundedMean)
    assert isinstance(bm1.quick_result([1.5, 2, 2.5]), float)

    bm2 = BoundedMean(epsilon=3.4, dtype="int")
    assert isinstance(bm2, BoundedMean)
    # assert isinstance(bm2.quick_result([1.5, 2, 2.5]), float)


def test_bounded_mean_int64():
    example_list = [5] * 100000000
    x = BoundedMean(1.0, 0, 10, dtype="int64")
    for _ in range(5):
        x.add_entries(example_list)

    assert expect_near(5.0, x.result(), 0.1)


def test_serialize_merge():
    bm1 = BoundedMean(1, 1, 10)
    bm2 = BoundedMean(1, 1, 10)
    bm1.add_entries([1 for i in range(100)])
    bm2.add_entries([10 for i in range(100)])

    serializer = bm1.serialize()
    bm2.merge(serializer)
    assert 3 <= bm2.result() <= 7


def test_result_crash():
    bm1 = BoundedMean(1, 1, 10)
    bm1.add_entries([1 for i in range(100)])
    bm1.result()
    with pytest.raises(RuntimeError):
        bm1.result()


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

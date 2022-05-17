# third party
import pytest

# pydp absolute
from pydp.algorithms.laplacian import Count


@pytest.mark.parametrize("dtype_in", ["int", "int64", "float"])
class TestPercentile:
    def test_basic(self, dtype_in):
        c = [1, 2, 3, 4, 2, 3]
        count = Count(epsilon=1.7, dtype=dtype_in)
        count.quick_result(c)

    def test_repeated_result(self, dtype_in):
        c = [1, 2, 3, 4, 2, 3]
        count = Count(epsilon=1.7, dtype=dtype_in)
        count.add_entries(c)

        count.result(0.5)

    """
    # TODO: port ConfidenceInterval

    def test_confidence_interval(self, input_class):
        epsilon = 0.5
        level = 0.95

        count = input_class(epsilon)

        count.noise_confidence_interval(level)

        count.partial_result().error_report().noise_confidence_interval(level)
    """

    """
    # TODO: port Summary
    def test_serialize(self, input_class):
        count = input_class(0.5)

        count.serialize()
    """

    """
    # TODO
    def test_memory(self, input_class):
        count = input_class()
        assert count.memory_used() == 0
    """


class TestCountDataTypes:
    def test_count_datatypes(self):
        count = Count(2.0, dtype="int")
        assert isinstance(count, Count)

        countae = count.add_entry(2)
        assert isinstance(countae, type(None))
        countaes = count.add_entries([4, 6, 8])
        assert isinstance(countaes, type(None))
        mem = count.memory_used()
        assert isinstance(mem, int)
        par = count.result()
        assert isinstance(par, int)

        res = count.quick_result([2])
        assert isinstance(res, int)


@pytest.mark.parametrize("dtype_in", ["int", "float"])
class TestCount:
    def test_basic(self, dtype_in):
        n = 100
        c = [1 for _ in range(100)]
        count = Count(epsilon=1, dtype=dtype_in)
        assert n - 10 < count.quick_result(c) < n + 10

    def test_l0_linf(self, dtype_in):
        n = 100
        c = [1 for _ in range(100)]
        count = Count(epsilon=1, l0_sensitivity=1, linf_sensitivity=1, dtype=dtype_in)
        assert n - 10 < count.quick_result(c) < n + 10


# TODO: port the following tests
#
# TEST(CountTest, MergeTest)
#

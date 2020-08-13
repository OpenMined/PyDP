import pytest
from pydp.algorithms.laplacian import Count


@pytest.mark.parametrize("dtype_in", ["int", "float"])
class TestPercentile:
    def test_basic(self, dtype_in):
        c = [1, 2, 3, 4, 2, 3]
        count = Count(epsilon=1.7, dtype=dtype_in)
        count.result(c)

    def test_repeated_result(self, dtype_in):
        c = [1, 2, 3, 4, 2, 3]
        count = Count(epsilon=1.7, dtype=dtype_in)
        count.add_entries(c)

        count.partial_result(0.5)

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
        mem = count.memory_used
        assert isinstance(mem, int)
        par = count.partial_result()
        assert isinstance(par, int)
        # TODO
        # par2 = count.partial_result(1.0)
        # assert isinstance(par2, int)
        res = count.result([2])
        assert isinstance(res, int)


# TODO: port the following tests
#
# TEST(CountTest, MergeTest)
#

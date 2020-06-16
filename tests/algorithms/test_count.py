import pytest
import pydp as dp


@pytest.mark.parametrize("input_class", [dp.CountInt, dp.CountDouble])
class TestPercentile:
    def test_basic(self, input_class):
        c = [1, 2, 3, 4, 2, 3]
        count = input_class()
        count.result(c)

    def test_basic_epsilon(self, input_class):
        c = [1, 2, 3, 4, 2, 3]
        count = input_class(1.7)
        count.result(c)

    def test_repeated_result(self, input_class):
        c = [1, 2, 3, 4, 2, 3]
        count = input_class()
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
        ci1 = dp.CountInt()
        ci2 = dp.CountInt(2.0)
        assert isinstance(ci1, dp.CountInt)
        assert isinstance(ci2, dp.CountInt)

        ci2ae = ci2.add_entry(2)
        assert isinstance(ci2ae, type(None))
        ci2aes = ci2.add_entries([4, 6, 8])
        assert isinstance(ci2aes, type(None))
        mem = ci2.memory_used()
        assert isinstance(mem, int)
        par = ci2.partial_result()
        assert isinstance(par, int)
        # TODO
        # par2 = ci2.partial_result(1.0)
        # assert isinstance(par2, int)
        res = ci2.result([2])
        assert isinstance(res, int)


# TODO: port the following tests
#
# TEST(CountTest, MergeTest)
#

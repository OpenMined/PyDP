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

    def test_memory(self, input_class):
        count = input_class()
        assert count.memory_used() == 0


# TODO: port the following tests
#
# TEST(CountTest, MergeTest)
#

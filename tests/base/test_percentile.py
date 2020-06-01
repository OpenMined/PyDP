import pytest
import pydp as dp


@pytest.mark.parametrize("input_class", [dp.PercentileInt, dp.PercentileDouble])
class TestPercentile:
    def test_empty_input_set(self, input_class):
        percentile = input_class()
        assert percentile.num_values() == 0
        assert (0.0, 1.0) == percentile.get_relative_rank(1)

    def test_singleton_input_set(self, input_class):
        percentile = input_class()
        percentile.add(1)
        assert percentile.num_values() == 1
        assert (0.0, 0.0) == percentile.get_relative_rank(0)
        assert (0.0, 1.0) == percentile.get_relative_rank(1)
        assert (1.0, 1.0) == percentile.get_relative_rank(10)

    def test_small_input_set(self, input_class):
        percentile = input_class()
        percentile.add(5)
        percentile.add(3)
        percentile.add(3)
        percentile.add(5)
        percentile.add(1)
        assert percentile.num_values() == 5
        assert (0.0, 0.0) == percentile.get_relative_rank(-1)
        assert (0.0, 0.2) == percentile.get_relative_rank(1)
        assert (0.2, 0.2) == percentile.get_relative_rank(2)
        assert (0.2, 0.6) == percentile.get_relative_rank(3)
        assert (0.6, 0.6) == percentile.get_relative_rank(4)
        assert (0.6, 1.0) == percentile.get_relative_rank(5)
        assert (1.0, 1.0) == percentile.get_relative_rank(6)

    def test_large_input_set(self, input_class):
        percentile = input_class()
        num_repeats = 3
        num_values = 10000

        for i in range(num_values, 0, -1):
            for j in range(num_repeats):
                percentile.add(i)

        assert (52.0 / num_values, 53.0 / num_values) == percentile.get_relative_rank(
            53
        )
        assert (0.0, 1.0 / num_values) == percentile.get_relative_rank(1)
        assert ((num_values - 1.0) / num_values, 1.0) == percentile.get_relative_rank(
            num_values
        )

    def test_reset(self, input_class):
        percentile = input_class()
        percentile.add(1)
        percentile.reset()
        assert percentile.num_values() == 0

    def test_memory(self, input_class):
        percentile = input_class()
        small_memory = percentile.memory()
        percentile.add(1)
        large_memory = percentile.memory()
        assert small_memory < large_memory


# TODO: port the following tests
#
# TYPED_TEST(PercentileTest, SerializeMerge)
#

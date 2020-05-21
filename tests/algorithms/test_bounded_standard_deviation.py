import pydp as dp


class TestBoundedStandardDeviation:
    def test_c_api(self):
        example_data = [1, 5, 7, 9, 13]
        epsilon = 1.0
        lower_bound, upper_bound = 0, 15
        bsd = dp.BoundedStandardDeviation(epsilon, lower_bound, upper_bound)
        result = bsd.result(example_data)
        assert type(result) is float and result >= 0
        assert result <= (upper_bound - lower_bound) / 2

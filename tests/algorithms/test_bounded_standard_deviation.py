# pydp absolute
from pydp.algorithms.laplacian import BoundedStandardDeviation


class TestBoundedStandardDeviation:
    def test_python_api(self):
        example_data = [1, 5, 7, 9, 13]
        epsilon = 1.0
        delta = 0
        lower_bound, upper_bound = 0, 15
        bsd = BoundedStandardDeviation(
            epsilon, delta, lower_bound, upper_bound, dtype="float"
        )
        result = bsd.quick_result(example_data)
        assert type(result) is float and result >= 0
        assert result <= (upper_bound - lower_bound) / 2

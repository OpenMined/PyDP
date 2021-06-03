# pydp absolute
from pydp.algorithms.laplacian import BoundedVariance


class TestBoundedVariance:
    def test_basic(self):
        example_data = [1, 5, 7, 9, 13]
        epsilon = 1.0
        delta = 0
        lower_bound, upper_bound = 0, 16
        bv = BoundedVariance(epsilon, delta, lower_bound, upper_bound, dtype="float")
        result = bv.quick_result(example_data)
        assert type(result) is float and result >= 0
        # Popoviciu's inequality on variances:
        assert result <= (upper_bound - lower_bound) ** 2 / 4

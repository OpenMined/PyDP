import pytest
import pydp as dp


class TestBoundedSum:
    def test_c_api_sanity_check(self):
        a = [1, 2, 3, 4]

        sum_algorithm = dp.BoundedSum(1.0, 0, 10)
        result = sum_algorithm.result(a)
        # The result value is -16.0
        # Google library tests make use of ZeroNoiseMechanism
        # for more reasonable expected values, but we don't support
        # setting Laplace mechanisms yet.
        assert type(result) is float

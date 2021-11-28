# third party
import pytest

# pydp absolute
from pydp.algorithms.laplacian import BoundedSum


class TestBoundedSum:
    def test_pythons_api_sanity_check(self):
        a = [1, 2, 3, 4]

        sum_algorithm = BoundedSum(1.0, 0, 0, 10, dtype="float")
        result = sum_algorithm.quick_result(a)
        # The result value is -16.0
        # Google library tests make use of ZeroNoiseMechanism
        # for more reasonable expected values, but we don't support
        # setting Laplace mechanisms yet.
        assert type(result) is float

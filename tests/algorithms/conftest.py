from typing import List
from itertools import accumulate
import math


def skew(samples: List[float], mu: float, sigma: float):
    """Unfortunately this is implemented in third_party/differential-privacy/cc/algorithms/distributions_test.cc
    and we don't want to pull the test files in. I'm assuming it'll be moved to
    third_party/differential-privacy/cc/algorithms/util.h If they (upstream) move it we can use it.
    Until then this should suffice. #FIXME: when possible we can fix this.
    """
    skew = list(
        accumulate(samples, lambda lhs, rhs: lhs + (rhs - mu) * (rhs - mu) * (rhs - mu))
    )[-1]
    return skew / (len(samples) * sigma * sigma * sigma)


def kurtosis(samples: List[float], mu: float, var: float):
    """Unfortunately this is implemented in third_party/differential-privacy/cc/algorithms/distributions_test.cc
    and we don't want to pull the test files in. I'm assuming it'll be moved to
    third_party/differential-privacy/cc/algorithms/util.h If they (upstream) move it we can use it.
    Until then this should suffice. #FIXME: when possible we can fix this.
    """
    kurt = list(
        accumulate(samples, lambda lhs, rhs: lhs + ((rhs - mu) * (rhs - mu)) ** 2)
    )[-1]
    n = len(samples)
    kurt = (n + 1) * kurt / (n * var * var)
    kurt -= 3 * (n - 1)
    kurt *= (n - 1) / (n - 2) / (n - 3)
    return kurt


def percentile(N, percent, key=lambda x: x):
    """
    Find the percentile of a list of values.
    @parameter N - is a list of values. Note N MUST BE already sorted.
    @parameter percent - a float value from 0.0 to 1.0.
    @parameter key - optional key function to compute value from each element of N.
    @return - the percentile of the values
    """
    if not N:
        return None
    k = (len(N) - 1) * percent
    f = math.floor(k)
    c = math.ceil(k)
    if f == c:
        return key(N[int(k)])
    d0 = key(N[int(f)]) * (c - k)
    d1 = key(N[int(c)]) * (k - f)
    return d0 + d1


# From what I understand @openmined/dp-research are going to look at validating correctness
# Until then we can use this to assert on floating point numbers.
# FIXME: When possible we should add 'correctness' tests.
expect_near = lambda expected, actual, tol: (
    expected + tol >= actual and expected - tol <= actual
)

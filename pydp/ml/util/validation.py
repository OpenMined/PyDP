from numbers import Real, Integral

import numpy as np


def check_epsilon_delta(epsilon, delta, allow_zero=False):
    """Checks that epsilon and delta are valid values for differential privacy.  Throws an error if checks fail,
    otherwise returns nothing.
    As well as the requirements of epsilon and delta separately, both cannot be simultaneously zero, unless
    ``allow_zero`` is set to ``True``.
    Parameters
    ----------
    epsilon : float
        Epsilon parameter for differential privacy.  Must be non-negative.
    delta : float
        Delta parameter for differential privacy.  Must be on the unit interval, [0, 1].
    allow_zero : bool, default: False
        Allow epsilon and delta both be zero.
    """
    if not isinstance(epsilon, Real) or not isinstance(delta, Real):
        raise TypeError("Epsilon and delta must be numeric")

    if epsilon < 0:
        raise ValueError("Epsilon must be non-negative")

    if not 0 <= delta <= 1:
        raise ValueError("Delta must be in [0, 1]")

    if not allow_zero and epsilon + delta == 0:
        raise ValueError("Epsilon and Delta cannot both be zero")
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

def check_bounds(bounds, shape=0, min_separation=0.0, dtype=float):
    """Input validation for the ``bounds`` parameter.
    Checks that ``bounds`` is composed of a list of tuples of the form (lower, upper), where lower <= upper and both
    are numeric.  Also checks that ``bounds`` contains the appropriate number of dimensions, and that there is a
    ``min_separation`` between the bounds.
    Parameters
    ----------
    bounds : tuple
        Tuple of bounds of the form (min, max). `min` and `max` can either be scalars or 1-dimensional arrays.
    shape : int, default: 0
        Number of dimensions to be expected in ``bounds``.
    min_separation : float, default: 0.0
        The minimum separation between `lower` and `upper` of each dimension.  This separation is enforced if not
        already satisfied.
    dtype : data-type, default: float
        Data type of the returned bounds.
    Returns
    -------
    bounds : tuple
    """
    if not isinstance(bounds, tuple):
        raise TypeError("Bounds must be specified as a tuple of (min, max), got {}.".format(type(bounds)))
    if not isinstance(shape, Integral):
        raise TypeError("shape parameter must be integer-valued, got {}.".format(type(shape)))

    lower, upper = bounds

    if np.asarray(lower).size == 1 or np.asarray(upper).size == 1:
        lower = np.ravel(lower).astype(dtype)
        upper = np.ravel(upper).astype(dtype)
    else:
        lower = np.asarray(lower, dtype=dtype)
        upper = np.asarray(upper, dtype=dtype)

    if lower.shape != upper.shape:
        raise ValueError("lower and upper bounds must be the same shape array")
    if lower.ndim > 1:
        raise ValueError("lower and upper bounds must be scalar or a 1-dimensional array")
    if lower.size != shape and lower.size != 1:
        raise ValueError("lower and upper bounds must have {} element(s), got {}.".format(shape or 1, lower.size))

    n_bounds = lower.shape[0]

    for i in range(n_bounds):
        _lower = lower[i]
        _upper = upper[i]

        if not isinstance(_lower, Real) or not isinstance(_upper, Real):
            raise TypeError("Each bound must be numeric, got {} ({}) and {} ({}).".format(_lower, type(_lower),
                                                                                          _upper, type(_upper)))

        if _lower > _upper:
            raise ValueError("For each bound, lower bound must be smaller than upper bound, got {}, {})".format(
                lower, upper))

        if _upper - _lower < min_separation:
            mid = (_upper + _lower) / 2
            lower[i] = mid - min_separation / 2
            upper[i] = mid + min_separation / 2

    if shape == 0:
        return lower.item(), upper.item()

    if n_bounds == 1:
        lower = np.ones(shape, dtype=dtype) * lower.item()
        upper = np.ones(shape, dtype=dtype) * upper.item()

    return lower, upper
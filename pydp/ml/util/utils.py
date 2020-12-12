import warnings

import numpy as np

from .validation import check_epsilon_delta

def global_seed(seed):
    """Sets the seed for all random number generators, to guarantee reproducibility in experiments.
    Parameters
    ----------
    seed : int
        The seed value for the random number generators.
    Returns
    -------
    None
    """
    np.random.seed(seed)

def copy_docstring(source):
    """Decorator function to copy a docstring from a `source` function to a `target` function.
    The docstring is only copied if a docstring is present in `source`, and if none is present in `target`.  Takes
    inspiration from similar in `matplotlib`.
    Parameters
    ----------
    source : method
        Source function from which to copy the docstring.  If ``source.__doc__`` is empty, do nothing.
    Returns
    -------
    target : method
        Target function with new docstring.
    """
    def copy_func(target):
        if source.__doc__ and not target.__doc__:
            target.__doc__ = source.__doc__
        return target
    return copy_func

class Budget(tuple):
    """Custom tuple subclass for privacy budgets of the form (epsilon, delta).
    The ``Budget`` class allows for correct comparison/ordering of privacy budget, ensuring that both epsilon and delta
    satisfy the comparison (tuples are compared lexicographically).  Additionally, tuples are represented with added
    verbosity, labelling epsilon and delta appropriately.
    Examples
    --------
    >>> from pydp.ml.util.utils import Budget
    >>> Budget(1, 0.5)
    (epsilon=1, delta=0.5)
    >>> Budget(2, 0) >= Budget(1, 0.5)
    False
    >>> (2, 0) >= (1, 0.5) # Tuples are compared with lexicographic ordering
    True
    """
    def __new__(cls, epsilon, delta):
        check_epsilon_delta(epsilon, delta, allow_zero=True)
        return tuple.__new__(cls, (epsilon, delta))

    def __gt__(self, other):
        if self.__ge__(other) and not self.__eq__(other):
            return True
        return False

    def __ge__(self, other):
        if self[0] >= other[0] and self[1] >= other[1]:
            return True
        return False

    def __lt__(self, other):
        if self.__le__(other) and not self.__eq__(other):
            return True
        return False

    def __le__(self, other):
        if self[0] <= other[0] and self[1] <= other[1]:
            return True
        return False

    def __repr__(self):
        return "(epsilon=%r, delta=%r)" % self

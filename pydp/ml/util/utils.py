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
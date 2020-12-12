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
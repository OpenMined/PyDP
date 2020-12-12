from numbers import Real

import numpy as np
from numpy.random import random

from .base import DPMechanism, TruncationAndFoldingMixin
from ..util.utils import copy_docstring
from pydp.distributions import LaplaceDistribution

class Laplace(DPMechanism):
    r"""
    The classic Laplace mechanism in differential privacy, as first proposed by Dwork, McSherry, Nissim and Smith.
    Paper link: https://link.springer.com/content/pdf/10.1007/11681878_14.pdf
    Includes extension to (relaxed) :math:`(\epsilon,\delta)`-differential privacy, as proposed by Holohan et al.
    Paper link: https://arxiv.org/pdf/1402.6124.pdf
    """
    def __init__(self):
        super().__init__()
        self._sensitivity = None

    def __repr__(self):
        output = super().__repr__()
        output += ".set_sensitivity(" + str(self._sensitivity) + ")" if self._sensitivity is not None else ""

        return output

    def set_sensitivity(self, sensitivity):
        """Sets the sensitivity of the mechanism.
        Parameters
        ----------
        sensitivity : float
            The sensitivity of the mechanism.  Must satisfy `sensitivity` > 0.
        Returns
        -------
        self : class
        """
        if not isinstance(sensitivity, Real):
            raise TypeError("Sensitivity must be numeric")

        if sensitivity < 0:
            raise ValueError("Sensitivity must be non-negative")

        self._sensitivity = float(sensitivity)
        return self

    def check_inputs(self, value):
        """Checks that all parameters of the mechanism have been initialised correctly, and that the mechanism is ready
        to be used.
        Parameters
        ----------
        value : float
            The value to be checked
        Returns
        -------
        True if the mechanism is ready to be used.
        Raises
        ------
        Exception
            If parameters have not been set correctly, or if `value` falls outside the domain of the mechanism.
        """
        super().check_inputs(value)

        if not isinstance(value, Real):
            raise TypeError("Value to be randomised must be a number")

        if self._sensitivity is None:
            raise ValueError("Sensitivity must be set")

        return True

    def get_bias(self, value):
        """Returns the bias of the mechanism at a given `value`.
        Parameters
        ----------
        value : int or float
            The value at which the bias of the mechanism is sought.
        Returns
        -------
        bias : float or None
            The bias of the mechanism at `value`.
        """
        return 0.0

    def get_variance(self, value):
        """Returns the variance of the mechanism at a given `value`.
        Parameters
        ----------
        value : float
            The value at which the variance of the mechanism is sought.
        Returns
        -------
        bias : float
            The variance of the mechanism at `value`.
        """
        self.check_inputs(0)

        return 2 * (self._sensitivity / (self._epsilon - np.log(1 - self._delta))) ** 2

    def randomise(self, value):
        """Randomise `value` with the mechanism.
        Parameters
        ----------
        value : float
            The value to be randomised.
        Returns
        -------
        float
            The randomised value.
        """
        self.check_inputs(value)

#         scale = self._sensitivity / (self._epsilon - np.log(1 - self._delta))

#         unif_rv = random() - 0.5

#         return value - scale * np.sign(unif_rv) * np.log(1 - 2 * np.abs(unif_rv))

        scale = self._sensitivity / (self._epsilon - np.log(1 - self._delta))
        
        dist = LaplaceDistribution(epsilon=self._epsilon, sensitivity=self._sensitivity)
        
        sample = dist.sample(scale=scale)

        return value - sample

# MIT License
#
# Copyright (C) IBM Corporation 2019
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
# documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit
# persons to whom the Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
# Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# Source:
# https://github.com/IBM/differential-privacy-library/blob/main/diffprivlib/mechanisms/geometric.py

# stdlib
import math
from numbers import Integral

# third party
import numpy as np
from numpy.random import random

# pydp absolute
from pydp.distributions import GeometricDistribution  # type: ignore

# pydp relative
from ..util.utils import copy_docstring
from .base import DPMechanism
from .base import TruncationAndFoldingMixin


class Geometric(DPMechanism):
    """
    The classic geometric mechanism for differential privacy, as first proposed by Ghosh, Roughgarden and Sundararajan.
    Extended to allow for non-unity sensitivity.
    Paper link: https://arxiv.org/pdf/0811.2841.pdf
    """

    def __init__(self):
        super().__init__()
        self._sensitivity = 1
        self._scale = None
        self._probability = None

    def __repr__(self):
        output = super().__repr__()
        output += (
            ".set_sensitivity(" + str(self._sensitivity) + ")"
            if self._sensitivity is not None
            else ""
        )

        return output

    def set_probability(self, probability):
        if probability == 0:
            raise ValueError("Probability cannot be zero")

        if not 0 <= probability <= 1:
            raise ValueError("Porbability must be in [0, 1]")

        if probability < 0:
            raise ValueError("Porbability must be non-negative")

        self._probability = probability
        return self

    def set_sensitivity(self, sensitivity):
        """Sets the sensitivity of the mechanism.
        Parameters
        ----------
        sensitivity : int
            The sensitivity of the mechanism.  Must satisfy `sensitivity` > 0.
        Returns
        -------
        self : class
        """
        if not isinstance(sensitivity, Integral):
            raise TypeError("Sensitivity must be an integer")

        if sensitivity < 0:
            raise ValueError("Sensitivity must be non-negative")

        self._sensitivity = sensitivity
        self._scale = None
        return self

    def check_inputs(self, value):
        """Checks that all parameters of the mechanism have been initialised correctly, and that the mechanism is ready
        to be used.
        Parameters
        ----------
        value : int
            The value to be checked.
        Returns
        -------
        True if the mechanism is ready to be used.
        Raises
        ------
        Exception
            If parameters have not been set correctly, or if `value` falls outside the domain of the mechanism.
        """
        super().check_inputs(value)

        if not isinstance(value, Integral):
            raise TypeError("Value to be randomised must be an integer")

        if self._scale is None:
            self._scale = (
                -self._epsilon / self._sensitivity
                if self._sensitivity > 0
                else -float("inf")
            )

    @copy_docstring(DPMechanism.get_bias)
    def get_bias(self, value):
        return 0.0

    @copy_docstring(DPMechanism.get_variance)
    def get_variance(self, value):
        self.check_inputs(value)

        leading_factor = (1 - np.exp(self._scale)) / (1 + np.exp(self._scale))
        geom_series = np.exp(self._scale) / (1 - np.exp(self._scale))

        return (
            2
            * leading_factor
            * (geom_series + 3 * (geom_series ** 2) + 2 * (geom_series ** 3))
        )

    def randomise(self, value):
        """Randomise `value` with the mechanism.
        Parameters
        ----------
        value : int
            The value to be randomised.
        Returns
        -------
        int
            The randomised value.
        """
        self.check_inputs(value)

        #         # Need to account for overlap of 0-value between distributions of different sign
        #         unif_rv = random() - 0.5
        #         unif_rv *= 1 + np.exp(self._scale)

        #         # Use formula for geometric distribution, with ratio of exp(-epsilon/sensitivity)
        #         return int(np.round(value + sgn * np.floor(np.log(sgn * unif_rv) / self._scale)))
        lambda_ = -1.0 * math.log(1 - self._probability)
        dist = GeometricDistribution(lambda_=lambda_)
        sample = dist.sample(-self._scale)
        return value + sample


class GeometricTruncated(Geometric, TruncationAndFoldingMixin):
    """
    The truncated geometric mechanism, where values that fall outside a pre-described range are mapped back to the
    closest point within the range.
    """

    def __init__(self):
        super().__init__()
        TruncationAndFoldingMixin.__init__(self)

    def __repr__(self):
        output = super().__repr__()
        output += TruncationAndFoldingMixin.__repr__(self)

        return output

    def set_bounds(self, lower, upper):
        """Sets the lower and upper bounds of the mechanism.
        For the truncated geometric mechanism, `lower` and `upper` must be integer-valued.  Must have
        `lower` <= `upper`.
        Parameters
        ----------
        lower : int
            The lower bound of the mechanism.
        upper : int
            The upper bound of the mechanism.
        Returns
        -------
        self : class
        """
        if not isinstance(lower, Integral) or not isinstance(upper, Integral):
            raise TypeError("Bounds must be integers")

        return super().set_bounds(lower, upper)

    @copy_docstring(DPMechanism.get_bias)
    def get_bias(self, value):
        raise NotImplementedError

    @copy_docstring(DPMechanism.get_bias)
    def get_variance(self, value):
        raise NotImplementedError

    @copy_docstring(Geometric.randomise)
    def randomise(self, value):
        TruncationAndFoldingMixin.check_inputs(self, value)

        noisy_value = super().randomise(value)
        return int(np.round(self._truncate(noisy_value)))

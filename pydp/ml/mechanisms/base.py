import abc
from copy import copy, deepcopy
from numbers import Real


class DPMachine(abc.ABC):
    """
    Parent class for :class:`.DPMechanism` and :class:`.DPTransformer`, providing and specifying basic functionality.
    """
    @abc.abstractmethod
    def randomise(self, value):
        """Randomise `value` with the mechanism.
        Parameters
        ----------
        value : int or float or str or method
            The value to be randomised.
        Returns
        -------
        int or float or str or method
            The randomised value, same type as `value`.
        """

    def copy(self):
        """Produces a copy of the class.
        Returns
        -------
        self : class
            Returns the copy.
        """
        return copy(self)

    def deepcopy(self):
        """Produces a deep copy of the class.
        Returns
        -------
        self : class
            Returns the deep copy.
        """
        return deepcopy(self)

    def set_epsilon(self, epsilon):
        r"""Sets the value of epsilon to be used by the mechanism.
        Parameters
        ----------
        epsilon : float
            The value of epsilon for achieving :math:`\epsilon`-differential privacy with the mechanism.  Must have
            `epsilon > 0`.
        Returns
        -------
        self : class
        """
        return self.set_epsilon_delta(epsilon, 0.0)

    @abc.abstractmethod
    def set_epsilon_delta(self, epsilon, delta):
        r"""Sets the value of epsilon and delta to be used by the mechanism.
        `epsilon` and `delta` cannot both be zero.
        Parameters
        ----------
        epsilon : float
            The value of epsilon for achieving :math:`(\epsilon,\delta)`-differential privacy with the mechanism.  Must
            have `epsilon >= 0`.
        delta : float
            The value of delta for achieving :math:`(\epsilon,\delta)`-differential privacy with the mechanism.
            Must have `0 <= delta <= 1`.
            `delta=0` gives strict (pure) differential privacy (:math:`\epsilon`-differential privacy).  `delta > 0`
            gives relaxed (approximate) differential privacy.
        Returns
        -------
        self : class
        """



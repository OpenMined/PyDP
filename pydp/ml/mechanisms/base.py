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


class DPMechanism(DPMachine, abc.ABC):
    r"""
    Base class for all mechanisms.  Instantiated from :class:`.DPMachine`.
    Notes
    -----
    * Each `DPMechanism` must define a `randomise` method, to handle the application of differential privacy
    * Mechanisms that only operate in a limited window of :math:`\epsilon` or :math:`\delta` must define a
      `set_epsilon_delta` method.  Error-checking, for example for non-zero :math:`\delta` should be done in
      `set_epsilon_delta`; `set_epsilon` should be left unchanged.
    * When new methods are added, `__repr__` should be updated accordingly in the mechanism.
    * Each mechanism's
    """
    def __init__(self):
        self._epsilon = None
        self._delta = None

    def __repr__(self):
        output = str(self.__module__) + "." + str(self.__class__.__name__) + "()"

        if self._epsilon is not None and self._delta is not None and self._delta > 0.0:
            output += ".set_epsilon_delta(" + str(self._epsilon) + "," + str(self._delta) + ")"
        elif self._epsilon is not None:
            output += ".set_epsilon(" + str(self._epsilon) + ")"

        return output

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

    def get_bias(self, value):
        """Returns the bias of the mechanism at a given `value`.
        Parameters
        ----------
        value : int or float
            The value at which the bias of the mechanism is sought.
        Returns
        -------
        bias : float or None
            The bias of the mechanism at `value` if defined, `None` otherwise.
        """
        raise NotImplementedError

    def get_variance(self, value):
        """Returns the variance of the mechanism at a given `value`.
        Parameters
        ----------
        value : int or float
            The value at which the variance of the mechanism is sought.
        Returns
        -------
        bias : float or None
            The variance of the mechanism at `value` if defined, `None` otherwise.
        """
        raise NotImplementedError

    def get_mse(self, value):
        """Returns the mean squared error (MSE) of the mechanism at a given `value`.
        Parameters
        ----------
        value : int or float
            The value at which the MSE of the mechanism is sought.
        Returns
        -------
        bias : float or None
            The MSE of the mechanism at `value` if defined, `None` otherwise.
        """
        return self.get_variance(value) + (self.get_bias(value)) ** 2

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
        Raises
        ------
        ValueError
            If `epsilon` is negative, or if `delta` falls outside [0,1], or if `epsilon` and `delta` are both zero.
        """
        if not isinstance(epsilon, Real) or not isinstance(delta, Real):
            raise TypeError("Epsilon and delta must be numeric")

        if epsilon < 0:
            raise ValueError("Epsilon must be non-negative")

        if not 0 <= delta <= 1:
            raise ValueError("Delta must be in [0, 1]")

        if epsilon + delta == 0:
            raise ValueError("Epsilon and Delta cannot both be zero")

        self._epsilon = float(epsilon)
        self._delta = float(delta)

        return self

    def check_inputs(self, value):
        """Checks that all parameters of the mechanism have been initialised correctly, and that the mechanism is ready
        to be used.
        Parameters
        ----------
        value : int or float or str or method
            The value to be checked.
        Returns
        -------
        True if the mechanism is ready to be used.
        Raises
        ------
        Exception
            If parameters have not been set correctly, or if `value` falls outside the domain of the mechanism.
        """
        del value
        if self._epsilon is None:
            raise ValueError("Epsilon must be set")
        return True



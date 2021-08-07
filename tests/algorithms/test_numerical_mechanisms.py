import numpy as np
import pytest
import pydp.algorithms.numerical_mechanisms as num_mech
from scipy.special import erfinv


REL_ERR_TOL = 1e-5


def assert_almost_eq(val_true, val_pred):
    return np.abs((val_true - val_pred) / val_true) < REL_ERR_TOL


def test_basic():
    num_mech_methods = {
        "add_noise",
        "noised_value_above_threshold",
        "memory_used",
        "noise_confidence_interval",
        "epsilon",
    }
    assert num_mech_methods.issubset(set(dir(num_mech.NumericalMechanism)))
    epsilon, delta, sensitivity = 1, 1e-7, 5.0
    with pytest.raises(TypeError):
        # This is a abstract class, it cannot be instantiated!
        obj = num_mech.NumericalMechanism(epsilon, delta)
    obj = num_mech.LaplaceMechanism(epsilon, sensitivity)
    assert num_mech_methods.issubset(set(dir(obj)))
    assert {
        # "deserialize",
        # "serialize",
        "get_uniform_double",
        "memory_used",
        "sensitivity",
        "diversity",
    }.issubset(set(dir(obj)))
    obj = num_mech.GaussianMechanism(epsilon, delta, sensitivity)
    assert num_mech_methods.issubset(set(dir(obj)))
    assert {
        # "deserialize",
        # "serialize",
        "memory_used",
        "l2_sensitivity",
        "std",
        "delta",
    }.issubset(set(dir(obj)))


def test_laplace_mechanism():
    epsilon, sensitivity = 1, 3.0
    laplace = num_mech.LaplaceMechanism(epsilon, sensitivity)
    value = 0
    value = laplace.add_noise(value)
    assert type(value) is int
    value = laplace.add_noise(value, 0.1)
    assert type(value) is int
    value = 0.0
    value = laplace.add_noise(value)
    assert type(value) is float
    value = laplace.add_noise(value, 0.1)
    assert type(value) is float
    conf_level = 0.5
    priv_budg = 0.1
    interval = laplace.noise_confidence_interval(0.5, 0.1, value)
    assert type(interval) is num_mech.ConfidenceInterval
    bound = laplace.diversity * np.log(1 - conf_level) / priv_budg
    lower_bound, upper_bound = value - bound, value + bound
    assert_almost_eq(lower_bound, interval.lower_bound)
    assert_almost_eq(upper_bound, interval.upper_bound)
    assert conf_level == interval.confidence_level


def test_gaussian_mechanism():
    epsilon, delta, l2_sensitivity = 1, 1e-5, 3.0
    gaussian = num_mech.GaussianMechanism(epsilon, delta, l2_sensitivity)
    value = 0
    value = gaussian.add_noise(value)
    assert type(value) is int
    value = gaussian.add_noise(value, 0.1)
    assert type(value) is int
    value = 0.0
    value = gaussian.add_noise(value)
    assert type(value) is float
    value = gaussian.add_noise(value, 0.1)
    assert type(value) is float
    conf_level = 0.5
    priv_budg = 0.1
    interval = gaussian.noise_confidence_interval(0.5, 0.1, value)
    local_gaussian = num_mech.GaussianMechanism(
        priv_budg * epsilon, priv_budg * delta, l2_sensitivity
    )
    assert type(interval) is num_mech.ConfidenceInterval
    bound = erfinv(-conf_level) * local_gaussian.std * (2 ** 0.5)
    lower_bound, upper_bound = value - bound, value + bound
    assert_almost_eq(lower_bound, interval.lower_bound)
    assert_almost_eq(upper_bound, interval.upper_bound)
    assert conf_level == interval.confidence_level

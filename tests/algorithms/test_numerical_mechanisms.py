import pytest
import pydp.algorithms.numerical_mechanisms as num_mech


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
        "deserialize",
        "get_uniform_double",
        "serialize",
        "memory_used",
        "sensitivity",
        "diversity",
    }.issubset(set(dir(obj)))
    obj = num_mech.GaussianMechanism(epsilon, delta, sensitivity)
    assert num_mech_methods.issubset(set(dir(obj)))
    assert {
        "deserialize",
        "serialize",
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
    print(laplace.noise_confidence_interval.__doc__)
    interval = laplace.noise_confidence_interval(0.5, 0.1, value)
    print(type(interval))

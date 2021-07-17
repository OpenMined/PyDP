#include <pybind11/pybind11.h>
#include "pybind11/complex.h"
#include "pybind11/functional.h"
#include "pybind11/stl.h"

#include "algorithms/distributions.h"
#include "algorithms/numerical-mechanisms.h"

#include "../pydp_lib/algorithm_builder.hpp"
#include "../pydp_lib/casting.hpp"

using namespace std;

namespace py = pybind11;
namespace dp = differential_privacy;

template <typename T>
py::class_<dp::NumericalMechanism>& DefPyAddNoise(
    py::class_<dp::NumericalMechanism>& pyclass) {
  using FunctorType = T (dp::NumericalMechanism::*)(T);
  return pyclass.def("add_noise",
                     static_cast<FunctorType>(&dp::NumericalMechanism::AddNoise),
                     py::arg("result"));
}

template <typename T, typename U>
py::class_<dp::NumericalMechanism>& DefPyAddNoise(
    py::class_<dp::NumericalMechanism>& pyclass) {
  using FunctorType = T (dp::NumericalMechanism::*)(T, U);
  return pyclass.def("add_noise",
                     static_cast<FunctorType>(&dp::NumericalMechanism::AddNoise),
                     py::arg("result"), py::arg("privacy_budget"));
}

template <typename T, typename U>
std::unique_ptr<T> downcast_unique_ptr(std::unique_ptr<U> u_ptr) {
  static_assert(std::is_base_of<U, T>::value, "Illegal downcast.");
  T* ptr = dynamic_cast<T*>(u_ptr.release());
  return std::unique_ptr<T>(ptr);
}

class NumericalMechanismBinder {
 public:
  static void DeclareIn(py::module& m) {
    py::class_<dp::NumericalMechanism> numerical_mech(m, "NumericalMechanism");
    numerical_mech.attr("__module__") = "pydp";
    DefPyAddNoise<int, double>(numerical_mech);
    DefPyAddNoise<int64_t, double>(numerical_mech);
    DefPyAddNoise<double, double>(numerical_mech);
    DefPyAddNoise<int>(numerical_mech);
    DefPyAddNoise<int64_t>(numerical_mech);
    DefPyAddNoise<double>(numerical_mech);
    numerical_mech
        .def("noised_value_above_threshold",
             &dp::NumericalMechanism::NoisedValueAboveThreshold)
        .def("memory_used", &dp::NumericalMechanism::MemoryUsed)
        .def("noise_confidence_interval",
             py::overload_cast<double, double, double>(
                 &dp::NumericalMechanism::NoiseConfidenceInterval),
             py::arg("confidence_level"), py::arg("privacy_budget"),
             py::arg("noised_result"))
        .def_property_readonly("epsilon", &dp::NumericalMechanism::GetEpsilon);
  }
};

class LaplaceMechanismBinder {
 public:
  static std::unique_ptr<dp::LaplaceMechanism> build(double epsilon,
                                                     double l1_sensitivity) {
    dp::LaplaceMechanism::Builder builder;
    builder.SetEpsilon(epsilon);
    builder.SetSensitivity(l1_sensitivity);
    builder.SetL1Sensitivity(l1_sensitivity);
    return downcast_unique_ptr<dp::LaplaceMechanism, dp::NumericalMechanism>(
        builder.Build().value());
  }

  static std::unique_ptr<dp::NumericalMechanismBuilder> clone() {
    dp::LaplaceMechanism::Builder cloner;
    return std::move(cloner.Clone());
  }

  static void DeclareIn(py::module& m) {
    py::class_<dp::LaplaceMechanism, dp::NumericalMechanism> lap_mech(
        m, "LaplaceMechanism");
    lap_mech.attr("__module__") = "pydp";
    lap_mech
        .def(py::init([](double epsilon, double sensitivity) {
               return build(epsilon, sensitivity);
             }),
             py::arg("epsilon"), py::arg("sensitivity") = 1.0)
        .def("deserialize", &dp::LaplaceMechanism::Deserialize)
        .def("noised_value_above_threshold",
             &dp::LaplaceMechanism::NoisedValueAboveThreshold)
        .def("get_uniform_double", &dp::LaplaceMechanism::GetUniformDouble)
        .def("noise_confidence_interval",
             py::overload_cast<double, double, double>(
                 &dp::LaplaceMechanism::NoiseConfidenceInterval),
             py::arg("confidence_level"), py::arg("privacy_budget"),
             py::arg("noised_result"))
        .def("serialize", &dp::LaplaceMechanism::Serialize)
        .def("memory_used", &dp::LaplaceMechanism::MemoryUsed)
        .def_property_readonly("sensitivity", &dp::LaplaceMechanism::GetSensitivity)
        .def_property_readonly("diversity", &dp::LaplaceMechanism::GetDiversity);
  }
};

class GaussianMechanismBinder {
 public:
  static std::unique_ptr<dp::GaussianMechanism> build(double epsilon, double delta,
                                                      double l2_sensitivity) {
    dp::GaussianMechanism::Builder builder;
    builder.SetEpsilon(epsilon);
    builder.SetDelta(delta);
    builder.SetL2Sensitivity(l2_sensitivity);
    return downcast_unique_ptr<dp::GaussianMechanism, dp::NumericalMechanism>(
        builder.Build().value());
  };

  static std::unique_ptr<dp::NumericalMechanismBuilder> clone() {
    dp::GaussianMechanism::Builder cloner;
    return std::move(cloner.Clone());
  };

  static void DeclareIn(py::module& m) {
    py::class_<dp::GaussianMechanism, dp::NumericalMechanism> gaus_mech(
        m, "GaussianMechanism");
    gaus_mech.attr("__module__") = "pydp";
    gaus_mech
        .def(py::init([](double epsilon, double delta, double l2_sensitivity) {
          return build(epsilon, delta, l2_sensitivity);
        }))
        .def("deserialize", &dp::GaussianMechanism::Deserialize)
        .def("noised_value_above_threshold",
             &dp::GaussianMechanism::NoisedValueAboveThreshold)
        .def("noise_confidence_interval",
             py::overload_cast<double, double, double>(
                 &dp::GaussianMechanism::NoiseConfidenceInterval),
             py::arg("confidence_level"), py::arg("privacy_budget"),
             py::arg("noised_result"))
        .def("serialize", &dp::GaussianMechanism::Serialize)
        .def("memory_used", &dp::GaussianMechanism::MemoryUsed)
        .def("calculate_stddev", &dp::GaussianMechanism::CalculateStddev)
        .def("calculate_delta", &dp::GaussianMechanism::CalculateDelta)
        .def_property_readonly("l2_sensitivity",
                               &dp::GaussianMechanism::GetL2Sensitivity);
  }
};

void init_mechanisms_mechanism(py::module& m) {
  NumericalMechanismBinder::DeclareIn(m);
  LaplaceMechanismBinder::DeclareIn(m);
  GaussianMechanismBinder::DeclareIn(m);
}

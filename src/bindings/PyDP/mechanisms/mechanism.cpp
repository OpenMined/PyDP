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

class ConfidenceIntervalBinder {
 public:
  static void DeclareIn(py::module& m) {
    py::class_<dp::ConfidenceInterval> confidence_interval(m, "ConfidenceInterval");
    confidence_interval.attr("__module__") = "pydp";
    confidence_interval
        .def_property("lower_bound", &dp::ConfidenceInterval::lower_bound,
                      &dp::ConfidenceInterval::set_lower_bound)
        .def_property("upper_bound", &dp::ConfidenceInterval::upper_bound,
                      &dp::ConfidenceInterval::set_upper_bound)
        .def_property("confidence_level", &dp::ConfidenceInterval::confidence_level,
                      &dp::ConfidenceInterval::set_confidence_level);
  }
};

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
    py::class_<dp::NumericalMechanism> numerical_mech(m, "NumericalMechanism",
                                                      R"pbdoc(
        Base class for all (Ɛ, 𝛿)-differenially private additive noise numerical mechanisms.
      )pbdoc");
    numerical_mech.attr("__module__") = "pydp";
    DefPyAddNoise<int, double>(numerical_mech);
    DefPyAddNoise<int64_t, double>(numerical_mech);
    DefPyAddNoise<double, double>(numerical_mech);
    DefPyAddNoise<int>(numerical_mech);
    DefPyAddNoise<int64_t>(numerical_mech);
    DefPyAddNoise<double>(numerical_mech);
    numerical_mech
        .def("noised_value_above_threshold",
             &dp::NumericalMechanism::NoisedValueAboveThreshold,
             R"pbdoc(
               Quickly determines if `result` with added noise is above certain `threshold`.
             )pbdoc")
        .def("memory_used", &dp::NumericalMechanism::MemoryUsed)
        .def(
            "noise_confidence_interval",
            [](dp::NumericalMechanism& self, double cl, double pb,
               double nr) -> dp::ConfidenceInterval {
              auto result = self.NoiseConfidenceInterval(cl, pb, nr);
              return result.ValueOrDie();
            },
            py::arg("confidence_level"), py::arg("privacy_budget"),
            py::arg("noised_result"),
            R"pbdoc(
              Returns the confidence interval of the specified confidence level of the
              noise that AddNoise() would add with the specified privacy budget.
              If the returned value is <x,y>, then the noise added has a confidence_level
              chance of being in the domain [x,y]
            )pbdoc")
        .def_property_readonly("epsilon", &dp::NumericalMechanism::GetEpsilon,
                               "The Ɛ of the numerical mechanism");
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
        .def("get_uniform_double", &dp::LaplaceMechanism::GetUniformDouble)
        // .def("deserialize", &dp::LaplaceMechanism::Deserialize)
        // .def("serialize", &dp::LaplaceMechanism::Serialize)
        .def_property_readonly("sensitivity", &dp::LaplaceMechanism::GetSensitivity,
                               "The L1 sensitivity of the query.")
        .def_property_readonly("diversity", &dp::LaplaceMechanism::GetDiversity,
                               "The diversity of the Laplace mechanism.");
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
        // .def("deserialize", &dp::GaussianMechanism::Deserialize)
        // .def("serialize", &dp::GaussianMechanism::Serialize)
        .def_property_readonly("delta", &dp::GaussianMechanism::GetDelta,
                               "The 𝛿 of the Gaussian mechanism.")
        .def_property_readonly(
            "std",
            [](const dp::GaussianMechanism& self) {
              return dp::GaussianMechanism::CalculateStddev(
                  self.GetEpsilon(), self.GetDelta(), self.GetL2Sensitivity());
            },
            R"pbdoc( 
              The standard deviation parameter of the 
              Gaussian mechanism underlying distribution. 
            )pbdoc")
        .def_property_readonly("l2_sensitivity",
                               &dp::GaussianMechanism::GetL2Sensitivity,
                               "The L2 sensitivity of the query.");
  }
};

void init_mechanisms_mechanism(py::module& m) {
  ConfidenceIntervalBinder::DeclareIn(m);
  NumericalMechanismBinder::DeclareIn(m);
  LaplaceMechanismBinder::DeclareIn(m);
  GaussianMechanismBinder::DeclareIn(m);
}

#include "pybind11/complex.h"
#include "pybind11/functional.h"
#include <pybind11/pybind11.h>
#include "pybind11/stl.h"

#include "algorithm/numerical_mechanism.h"

#include "../pydp_lib/algorithm_builder.hpp"
#include "../pydp_lib/casting.hpp"

using namespace std;

namespace py = pybind11;
namespace dp = differential_privacy;


dp.attr("kMaxOverflowProbability") = std::pow(2.0, -64);
dp.attr("kGaussianSigmaAccuracy") = 1e-3;

class declareNumericalMechanismClass {
 public: 
  void declareNumericalMechanism(py::module &m) {
    py::class_<dp::NumericalMechanism> numerical_mech(m, "NumericalMechanism");
    numerical_mech.attr("__module__") = "pydp";
    numerical_mech
        .def(py::init<double>()
        .def("AddNoise", &AddNoise<int, double>)
        .def("AddNoise", &AddNoise<int64_t, double>)
        .def("AddNoise", &AddNoise<double, double>)
        .def("AddNoise", &AddNoise<int>)
        .def("AddNoise", &AddNoise<int64_t>)
        .def("AddNoise", &AddNoise<double>)
        .def("NoisedValueAboveThreshold", &dp::NumericalMechanism::NoisedValueAboveThreshold<double, double>)
        .def("MemoryUsed", &dp::NumericalMechanism::MemoryUsed)
        .def("NoiseConfidenceInterval", py::overload_cast<double, double, double>(&dp::NumericalMechanism::<dp::ConfidenceInterval>NoiseConfidenceInterval),
            py::arg("confidence_level"), py::arg("privacy_budget"), py::arg("noised_result"))
        .def("NoiseConfidenceInterval", py::overload_cast<double, double>(&dp::NumericalMechanism::<dp::ConfidenceInterval>NoiseConfidenceInterval),
            py::arg("confidence_level"), py::arg("privacy_budget"))
        .def("GetEpsilon", &dp::NumericalMechanism::GetEpsilon)
        .def("GetVariance", &dp::NumericalMechanism::GetVariance)
        .def("AddDoubleNoise", &dp::NumericalMechanism::AddDoubleNoise<double, double>)
        .def("AddDoubleNoise", &dp::NumericalMechanism::AddInt64Noise<double, double>)
        .def("CheckConfidenceLevel", &dp::NumericalMechanism::CheckConfidenceLevel<double>)
        .def("CheckPrivacyBudget", &dp::NumericalMechanism::CheckPrivacyBudget<double>)
        .def("CheckAndClampBudget", &dp::NumericalMechanism::CheckAndClampBudget<double>)
        .def_property_readonly("epsilon", &dp::NumericalMechanism::epsilon);
  } 
};

class declareNumericalMechanismBuilder {
  public:
    std::unique_ptr<dp::NumericalMechanism> build() {
    dp::NumericalMechanism builder;
    return std::move(builder.Build().value());
  };
    std::unique_ptr<dp::NumericalMechanismBuilder> clone(val) {
    dp::NumericalMechanismBuilder cloner;
    cloner.SetEpsilon(val);
    cloner.SetDelta(val);
    cloner.SetL0Sensitivity(val);
    cloner.SetInfSensitivity(val);
    return std::move(cloner.Clone().value());
  };
    void declareNumericalMechanismBuilder(py::module &m) {
    py::class_<dp::NumericalMechanismBuilder> num_mech_builder(m, "NumericalMechanismBuilder");
    num_mech_builder.attr("__module__") = "pydp";
    num_mech_builder
        .def(py::init([this](double val) { return this->clone(val); }),
             py::arg("epsilon"), py::arg("delta"), py::arg("l0_sensitivity"), py::arg("linf_sensitivity"))
        .def("DeltaIsSetAndValid", &dp::NumericalMechanismBuilder::DeltaIsSetAndValid)
        .def_property_readonly("epslion", &dp::NumericalMechanismBuilder::epsilon)
        .def_property_readonly("delta", &dp::NumericalMechanismBuilder::delta)
        .def_property_readonly("l0_sensitivity", &dp::NumericalMechanismBuilder::l0_sensitivity)
        .def_property_readonly("linf_sensitivity", &dp::NumericalMechanismBuilder::linf_sensitivity);
  }
};

class 

void init_mechanisms_mechanism(py::module& m) {
  declareNumericalMechanism(m);
  m.def(py::init<>())

  declareLaplaceDistributionClass laplace_obj = declareLaplaceDistributionClass();
  laplace_obj.declareLaplaceDistribution(m);
  declareGaussianDistributionClass gaussian_obj = declareGaussianDistributionClass();
  gaussian_obj.declareGaussianDistribution(m);
  declareGeometricDistributionClass geom_obj = declareGeometricDistributionClass();
  geom_obj.declareGeometricDistribution(m);
}


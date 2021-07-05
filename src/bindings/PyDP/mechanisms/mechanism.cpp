#include "pybind11/complex.h"
#include "pybind11/functional.h"
#include <pybind11/pybind11.h>
#include "pybind11/stl.h"

#include "algorithm/numerical_mechanism.h"

#include "../pydp_lib/algorithm_builder.hpp"
#include "../pydp_lib/casting.hpp"
#include "../algorithms/distributions.cpp"

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
        .def(py::init<double>())
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
        .def("GetEpsilon", &dp::NumericalMechanism::GetEpsilon)
        .def("GetVariance", &dp::NumericalMechanism::GetVariance)
        .def("AddDoubleNoise", &dp::NumericalMechanism::AddDoubleNoise<double, double>)
        .def("AddInt64Noise", &dp::NumericalMechanism::AddInt64Noise<double, double>)
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

class declareLaplaceMechanism {
  public:
    std::unique_ptr<dp::NumericalMechanism> build(double l1_sensitivity) {
    dp::NumericalMechanismBuilder::Builder builder;
    builder.SetSensitivity(l1_sensitivity);
    builder.SetL1Sensitivity(l1_sensitivity);
    return std::move(builder.Build().value());
  };

    std::unique_ptr<dp::NumericalMechanismBuilder> clone() {
    dp::NumericalMechanismBuilder cloner;
    return std::move(cloner.Clone().value());
  };

    void declareLaplaceMechanism(py::module &m) {
      py::class_<dp::LaplaceMechanism, dp::NumericalMechanism> lap_mech(m, "LaplaceMechanism");
      lap_mech.attr("__module__") = "pydp";
      lap_mech
          .def(py::init<>())
          .def(py::init([this](double epsilon, double sensitivity) {}),
             py::arg("sensitivity") = 1.0)
          .def(py::init([this](double epsilon, double sensitivity, std::unique_ptr<internal::dp::LaplaceDistribution>) {
            return this->build(epsilon, sensitivity);
          }),
            py::arg("epsilon") = 0., py::arg("sensitivity"))
          .def("GetL1Sensitivity", &dp::LaplaceMechanism::GetL1Sensitivity)
          .def("CalculateL1Sensitivity", &dp::LaplaceMechanism::CalculateL1Sensitivity)
          .def("Deserialize", &dp::LaplaceMechanism::Deserialize)
          .def("NoisedValueAboveThreshold", &dp::LaplaceMechanism::NoisedValueAboveThreshold)
          .def("GetUniformDouble", &dp::LaplaceMechanism::GetUniformDouble)
          .def("NoiseConfidenceInterval", py::overload_cast<double, double, double>(&dp::LaplaceMechanism::<dp::ConfidenceInterval>NoiseConfidenceInterval),
            py::arg("confidence_level"), py::arg("privacy_budget"), py::arg("noised_result"))
          .def("Serialize", &dp::serialization::LaplaceMechanism::Serialize)
          .def("MemoryUsed", &dp::LaplaceMechanism::MemoryUsed)
          .def("GetSensitivity", &dp::LaplaceMechanism::GetSensitivity)
          .def("GetDiversity", &dp::LaplaceMechanism::GetDiversity)
          .def("GetMinEpsilon", &dp::LaplaceMechanism::GetMinEpsilon)
          .def("GetVariance", &dp::LaplaceMechanism::GetVariance)
          .def("AddDoubleNoise", &dp::LaplaceMechanism::AddDoubleNoise)
          .def("AddInt64Noise", &dp::LaplaceMechanism::AddInt64Noise)
          .def_property_readonly("sensitivity", &dp::LaplaceMechanism::sensitivity)
          .def_property_readonly("diversity", &dp::LaplaceMechanism::diversity)
          .def_property_readonly("distro", std::unique_ptr<internal::dp::LaplaceDistribution>::&dp::LaplaceMechansim::distro);
  }
};

class declareGaussianMechanism {
  public:
    std::unique_ptr<dp::NumericalMechanism> build(double l2_sensitivity) {
    dp::NumericalMechanismBuilder::Builder builder;
    builder.SetL2Sensitivity(l2_sensitivity);
    return std::move(builder.Build().value());
  };

    std::unique_ptr<dp::NumericalMechanismBuilder> clone() {
    dp::NumericalMechanismBuilder cloner;
    return std::move(cloner.Clone().value());
  };

    void declareGaussianMechanism(py::module &m) {
      py::class_<dp::GaussianMechanism, dp::NumericalMechanism> gaus_mech(m, "GaussianMechanism");
      gaus_mech.attr("__module__") = "pydp";
      gaus_mech
          .def(py::init<>())
          .def(py::init([this](double epsilon, double delta, double l2_sensitivity) {
            return this->build(epsilon, delta, l2_sensitivity);
          }))
          .def(py::init([this](double epsilon, double delta, double l2_sensitivity, std::unique_ptr<internal::dp::LaplaceDistribution>) {
            return this->build(epsilon, delta, l2_sensitivity);
          }))
          .def("CalculateL2Sensitivity", &dp::GaussianMechanism::CalculateL2Sensitivity)
          .def("Deserialize", std::unique_ptr<NumericalMechanism>::&dp::GaussianMechanism::Deserialize)
          .def("NoisedValueAboveThreshold", &dp::GaussianMechanism::NoisedValueAboveThreshold)
          .def("NoiseConfidenceInterval", py::overload_cast<double, double, double>(&dp::GaussianMechanism::<dp::ConfidenceInterval>NoiseConfidenceInterval),
            py::arg("confidence_level"), py::arg("privacy_budget"), py::arg("noised_result"))
          .def("Serialize", &dp::serialization::GaussianMechanism::Serialize)
          .def("MemoryUsed", &dp::GaussianMechanism::MemoryUsed)
          .def("CalculateStddev", &dp::GaussianMechanism::CalculateStddev)
          .def("GetDelta", &dp::GaussianMechanism::GetDelta)
          .def("GetL2Sensitivity", &dp::GaussianMechanism::GetL2Sensitivity)
          .def("GetVariance", &dp::GaussianMechanism::GetVariance)
          .def("CalculateDelta", &dp::GaussianMechanism::CalculateDelta)
          .def("AddDoubleNoise", &dp::GaussianMechanism::AddDoubleNoise)
          .def("AddInt64Noise", &dp::GaussianMechanism::AddInt64Noise)
          .def_property_readonly("l2_sensitivity", &dp::GaussianMechanism::l2_sensitivity)
          .def_property_readonly("delta", &dp::GaussianMechanism::delta)
          .def_property_readonly("distro", std::unique_ptr<internal::dp::GaussianDistribution> distro)
          .def("StandardNormalDistributionCDF", &dp::GaussianMechanism::StandardNormalDistributionCDF);
  }
};

class declareMinVarianceMechanismBuilder {
  public:
    /* need some work around here */
    std::unique_ptr<dp::NumericalMechanism> build(double l2_sensitivity) {
    dp::NumericalMechanismBuilder::Builder builder;
    builder.SetL2Sensitivity(l2_sensitivity);
    return std::move(builder.Build().value());
  };

    std::unique_ptr<dp::NumericalMechanismBuilder> clone() {
    dp::NumericalMechanismBuilder cloner;
    return std::move(cloner.Clone().value());
  };

    void declareMinVarianceMechanismBuilder(py::module &m) {
      py::class_<dp::MinVarianceMechanismBuilder, dp::NumericalMechanismBuilder> min_varmech(m, "MinVarianceMechanismBuilder");
      min_varmech.attr("__module__") = "pydp";
      min_varmech
          .def("GetMechanismFromBuilder", std::unique_ptr<dp::NumericalMechanism>::&dp::GaussianMechanism::GetMechanismFromBuilder);
  }
};

void init_mechanisms_mechanism(py::module& m) {
  declareNumericalMechanismBuilder num_builder_obj = declareNumericalMechanismBuilder();
  num_builder_obj.declareNumericalMechanismBuilder(m);
  declareLaplaceMechanism laplace_obj = declareLaplaceMechanism();
  laplace_obj.declareLaplaceMechanism(m);
  declareGaussianMechanism gaussian_obj = declareGaussianMechanism();
  gaussian_obj.declareGaussianMechanism(m);
  declareMinVarianceMechanismBuilder minvar_obj = declareMinVarianceMechanismBuilder();
  minvar_obj.declareMinVarianceMechanismBuilder(m);
}


// Provides bindings for Partition Selection strategies.

#include "algorithms/partition-selection.h"
#include "pybind11/complex.h"
#include "pybind11/functional.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

namespace py = pybind11;
namespace dp = differential_privacy;

template <class Strategy>
std::unique_ptr<dp::PartitionSelectionStrategy> CreatePartitionStrategy(
    double epsilon, double delta, int max_partitions_contributed) {
  typename Strategy::Builder builder;
  builder.SetEpsilon(epsilon);
  builder.SetDelta(delta);
  builder.SetMaxPartitionsContributed(max_partitions_contributed);

  auto obj = builder.Build();
  if (!obj.ok()) {
    throw std::runtime_error(obj.status().ToString());
  }
  return std::move(obj.value());
}

std::unique_ptr<dp::PartitionSelectionStrategy> CreatePreThresholdingStrategy(
    double epsilon, double delta, int max_partitions_contributed, int pre_threshold,
    dp::PartitionSelectionStrategyWithPreThresholding::PartitionSelectionStrategyType
        strategy_type) {
  typename dp::PartitionSelectionStrategyWithPreThresholding::Builder builder;
  builder.SetEpsilon(epsilon);
  builder.SetDelta(delta);
  builder.SetMaxPartitionsContributed(max_partitions_contributed);
  builder.SetPreThreshold(pre_threshold);
  builder.SetPartitionSelectionStrategy(strategy_type);

  auto obj = builder.Build();
  if (!obj.ok()) {
    throw std::runtime_error(obj.status().ToString());
  }
  return std::move(obj.value());
}

template <class Strategy>
py::class_<Strategy> init_partition_selection_strategy(py::module& m,
                                                       const std::string& strategy_name,
                                                       const std::string& docstring) {
  auto py_class =
      py::class_<Strategy>(m, strategy_name.c_str(), R"pbdoc(" + docstring + )pbdoc");
  py_class
      .def("should_keep", &Strategy::ShouldKeep, py::arg("num_users"),
           R"pbdoc(
              Decides whether or not to keep a partition with `num_users` based on differential privacy parameters and strategy.
            )pbdoc")
      .def("probability_of_keep", &Strategy::ProbabilityOfKeep, py::arg("num_users"),
           R"pbdoc(
              Probability of keeping a partition with `num_users` based on differential privacy parameters and strategy.
            )pbdoc")
      .def_property_readonly("epsilon", &dp::PartitionSelectionStrategy::GetEpsilon)
      .def_property_readonly("delta", &dp::PartitionSelectionStrategy::GetDelta)
      .def_property_readonly(
          "max_partitions_contributed",
          &dp::PartitionSelectionStrategy::GetMaxPartitionsContributed)
      .attr("__module__") = "_partition_selection";
  return py_class;
}

template <class Strategy>
void add_thresholding_specific_methods(py::class_<Strategy>* py_class) {
  py_class
      ->def("noised_value_if_should_keep", &Strategy::NoiseValueIfShouldKeep,
            py::arg("num_users"),
            R"pbdoc(
              Decides whether or not to keep a partition with `num_users` and
              returns `num_users` + noise if the partition should be kept.
            )pbdoc")
      .def_property_readonly("threshold", &Strategy::GetThreshold);
}

void init_algorithms_partition_selection_strategies(py::module& m) {
  // Truncated Geometric Partition selection strategy.
  init_partition_selection_strategy<dp::NearTruncatedGeometricPartitionSelection>(
      m, "TruncatedGeometricPartitionSelectionStrategy",
      "Truncated Geometric (epsilon, delta)-differenially private partition "
      "selection strategy.");
  m.def("create_truncated_geometric_partition_strategy",
        &CreatePartitionStrategy<dp::NearTruncatedGeometricPartitionSelection>,
        py::arg("epsilon"), py::arg("delta"), py::arg("max_partitions_contributed"));

  // Laplace Partition selection strategy.
  py::class_<dp::LaplacePartitionSelection> py_laplace_strategy_class =
      init_partition_selection_strategy<dp::LaplacePartitionSelection>(
          m, "LaplacePartitionSelectionStrategy",
          "Laplace (epsilon, delta)-differenially private partition "
          "selection strategy.");

  add_thresholding_specific_methods<dp::LaplacePartitionSelection>(
      &py_laplace_strategy_class);

  m.def("create_laplace_partition_strategy",
        &CreatePartitionStrategy<dp::LaplacePartitionSelection>, py::arg("epsilon"),
        py::arg("delta"), py::arg("max_partitions_contributed"));

  // Gaussian Partition selection strategy.
  py::class_<dp::GaussianPartitionSelection> py_gaussian_strategy_class =
      init_partition_selection_strategy<dp::GaussianPartitionSelection>(
          m, "GaussianPartitionSelectionStrategy",
          "Gaussian (epsilon, delta)-differenially private partition "
          "selection strategy.");

  add_thresholding_specific_methods<dp::GaussianPartitionSelection>(
      &py_gaussian_strategy_class);

  m.def("create_gaussian_partition_strategy",
        &CreatePartitionStrategy<dp::GaussianPartitionSelection>, py::arg("epsilon"),
        py::arg("delta"), py::arg("max_partitions_contributed"));

  // Pre-thresholding partition selection strategy.
  py::class_<dp::PartitionSelectionStrategyWithPreThresholding>
      py_pre_thresholding_strategy_class = init_partition_selection_strategy<
          dp::PartitionSelectionStrategyWithPreThresholding>(
          m, "PreThresholdingPartitionSelectionStrategy",
          "(epsilon, delta)-differenially private partition selection "
          "strategy with pre-thresholding.");

  py_pre_thresholding_strategy_class.def_property_readonly(
      "pre_threshold",
      &dp::PartitionSelectionStrategyWithPreThresholding::GetPreThreshold);

  py::enum_<dp::PartitionSelectionStrategyWithPreThresholding::
                PartitionSelectionStrategyType>(m, "PartitionSelectionStrategyType")
      .value("NEAR_TRUNCATED_GEOMETRIC",
             dp::PartitionSelectionStrategyWithPreThresholding::
                 PartitionSelectionStrategyType::kNearTruncatedGeometric)
      .value("LAPLACE", dp::PartitionSelectionStrategyWithPreThresholding::
                            PartitionSelectionStrategyType::kLaplace)
      .value("GAUSSIAN", dp::PartitionSelectionStrategyWithPreThresholding::
                             PartitionSelectionStrategyType::kGaussian)
      .export_values();

  m.def("create_pre_thresholding_partition_strategy", &CreatePreThresholdingStrategy,
        py::arg("epsilon"), py::arg("delta"), py::arg("max_partitions_contributed"),
        py::arg("pre_threshold"), py::arg("strategy_type"));
}

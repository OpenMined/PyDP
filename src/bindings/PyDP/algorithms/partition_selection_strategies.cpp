// Provides bindings for Bounded Functions

#include "pybind11/complex.h"
#include "pybind11/functional.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include "algorithms/algorithm.h"
#include "algorithms/partition-selection.h"

#include "../pydp_lib/algorithm_builder.hpp"
#include "../pydp_lib/casting.hpp"  // our caster helper library

using namespace std;

namespace py = pybind11;
namespace dp = differential_privacy;

typedef std::unique_ptr<dp::PartitionSelectionStrategy> PyPartitionSelectionStrategy;

PyPartitionSelectionStrategy create_truncted_geometric_partition_strategy(
    double epsilon, double delta, int max_partitions, double adjusted_delta) {
  return std::make_unique<dp::PreaggPartitionSelection>(epsilon, delta, max_partitions,
                                                        adjusted_delta);
}

PyPartitionSelectionStrategy create_laplace_partition_strategy(
    double epsilon, double delta, int64_t max_partitions_contributed,
    double adjusted_delta, double threshold,
    std::unique_ptr<dp::NumericalMechanism> laplace) {

  return std::make_unique<dp::LaplacePartitionSelection>(
      epsilon, delta, max_partitions_contributed, adjusted_delta, threshold, laplace);
}

PyPartitionSelectionStrategy create_gaussian_partition_strategy(
    double epsilon, double delta, double threshold_delta, double noise_delta,
    int64_t max_partitions_contributed, double adjusted_delta, double threshold,
    std::unique_ptr<dp::NumericalMechanism> gaussian) {

  return std::make_unique<dp::GaussianPartitionSelection>(
      epsilon, delta, threshold_delta, noise_delta, max_partitions_contributed,
      adjusted_delta, threshold, gaussian);
}

void init_algorithms_partition_selection_strategies(py::module& m) {
  py::class_<dp::PartitionSelectionStrategy>(m, "PartitionSelectionStrategy")
      .def("ShouldKeep", &dp::PartitionSelectionStrategy::ShouldKeep);

  m.def("create_truncted_geometric_partition_strategy",
        create_truncted_geometric_partition_strategy);
  m.def("create_laplace_partition_strategy", create_laplace_partition_strategy);
  m.def("create_gaussian_partition_strategy", create_gaussian_partition_strategy);
}

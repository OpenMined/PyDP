// Provides bindings for Bounded Functions

#include "pybind11/complex.h"
#include "pybind11/functional.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include "algorithms/partition-selection.h"

using namespace std;

namespace py = pybind11;
namespace dp = differential_privacy;

typedef std::unique_ptr<dp::PartitionSelectionStrategy> PyPartitionSelectionStrategy;

PyPartitionSelectionStrategy create_truncted_geometric_partition_strategy(
    double epsilon, double delta, int max_partitions_contributed) {
  dp::PreaggPartitionSelection::Builder builder;
  builder.SetEpsilon(epsilon);
  builder.SetDelta(delta);
  builder.SetMaxPartitionsContributed(max_partitions_contributed);

  auto obj = builder.Build();
  if (!obj.ok()) {
    throw std::runtime_error(obj.status().ToString());
  }
  return std::move(obj.ValueOrDie());
}

PyPartitionSelectionStrategy create_laplace_partition_strategy(
    double epsilon, double delta, int max_partitions_contributed
    ) {
  dp::LaplacePartitionSelection::Builder builder;
  builder.SetEpsilon(epsilon);
  builder.SetDelta(delta);
  builder.SetMaxPartitionsContributed(max_partitions_contributed);
  // builder.SetLaplaceMechanism(std::move(laplace_builder));

  auto obj = builder.Build();
  if (!obj.ok()) {
    throw std::runtime_error(obj.status().ToString());
  }
  return std::move(obj.ValueOrDie());
}

PyPartitionSelectionStrategy create_gaussian_partition_strategy(
    double epsilon, double delta, int max_partitions_contributed
    ) {
  dp::GaussianPartitionSelection::Builder builder;
  builder.SetEpsilon(epsilon);
  builder.SetDelta(delta);
  builder.SetMaxPartitionsContributed(max_partitions_contributed);
  // builder.SetGaussianMechanism(std::move(gaussian_builder));

  auto obj = builder.Build();
  if (!obj.ok()) {
    throw std::runtime_error(obj.status().ToString());
  }
  return std::move(obj.ValueOrDie());
}

void init_algorithms_partition_selection_strategies(py::module& m) {
  py::class_<dp::PartitionSelectionStrategy, PyPartitionSelectionStrategy>(m, "PartitionSelectionStrategy")
      .def("ShouldKeep", &dp::PartitionSelectionStrategy::ShouldKeep)
      .attr("__module__") = "_algorithms";

  m.def("create_truncted_geometric_partition_strategy",
        &create_truncted_geometric_partition_strategy);
  m.def("create_laplace_partition_strategy", &create_laplace_partition_strategy);
  m.def("create_gaussian_partition_strategy", &create_gaussian_partition_strategy);
}

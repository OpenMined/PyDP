// Bindings for QuantileTree, which allows to compute multiple DP quantiles.

#include "algorithms/numerical-mechanisms.h"
#include "algorithms/quantile-tree.h"
#include "pybind11/complex.h"
#include "pybind11/functional.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

namespace py = pybind11;
namespace dp = differential_privacy;

namespace {
std::unique_ptr<dp::QuantileTree<double>> CreateQuantileTree(double lower, double upper,
                                                             int tree_height,
                                                             int branching_factor) {
  dp::QuantileTree<double>::Builder builder;
  builder.SetLower(lower);
  builder.SetUpper(upper);
  builder.SetTreeHeight(tree_height);
  builder.SetBranchingFactor(branching_factor);

  auto obj = builder.Build();
  if (!obj.ok()) {
    throw py::value_error("Error in creating QuantileTree. Status=" +
                          obj.status().ToString());
  }
  return std::move(obj.value());
}

dp::QuantileTree<double>::Privatized GetPrivatizeTree(
    dp::QuantileTree<double>& tree, double epsilon, double delta,
    int max_partitions_contributed, int max_contributions_per_partition,
    const std::string& noise_type) {
  dp::QuantileTree<double>::DPParams dp_params;
  dp_params.epsilon = epsilon;
  dp_params.delta = delta;
  dp_params.max_contributions_per_partition = max_contributions_per_partition;
  dp_params.max_partitions_contributed_to = max_partitions_contributed;
  // Create DP mechanism.
  if (noise_type == "laplace") {
    dp_params.mechanism_builder = std::make_unique<dp::LaplaceMechanism::Builder>();
  } else if (noise_type == "gaussian") {
    dp_params.mechanism_builder = std::make_unique<dp::GaussianMechanism::Builder>();
  } else {
    throw py::value_error("noise_type can be 'laplace' or 'gaussian', but it is '" +
                          noise_type + "'.");
  }
  auto status_or_result = tree.MakePrivate(dp_params);
  if (!status_or_result.ok()) {
    throw std::runtime_error("Error in computing DP quantiles. Status=" +
                             status_or_result.status().ToString());
  }
  return std::move(status_or_result.value());
}
}  // namespace

struct QuantileConfidenceInterval {
  double quantile;
  double lower_bound;
  double upper_bound;
};

void init_algorithms_quantile_tree(py::module& m) {
  py::class_<QuantileConfidenceInterval>(m, "QuantileConfidenceInterval")
      .def_readonly("quantile", &QuantileConfidenceInterval::quantile)
      .def_readonly("lower_bound", &QuantileConfidenceInterval::lower_bound)
      .def_readonly("upper_bound", &QuantileConfidenceInterval::upper_bound);

  auto py_class = py::class_<dp::QuantileTree<double>>(m, "QuantileTree",
                                                       R"pbdoc(
        Class for computing differentially private quantiles.
      )pbdoc");

  py_class.def(
      py::init([](double lower, double upper, int tree_height, int branching_factor) {
        return CreateQuantileTree(lower, upper, tree_height, branching_factor);
      }),
      py::arg("lower"), py::arg("upper"), py::arg("tree_height"),
      py::arg("branching_factor"));
  py_class.def_property_readonly("height", &dp::QuantileTree<double>::GetHeight);
  py_class.def_property_readonly("branching_factor",
                                 &dp::QuantileTree<double>::GetBranchingFactor);
  py_class.def_property_readonly("memory_used", &dp::QuantileTree<double>::MemoryUsed);
  py_class.def("add_entry", &dp::QuantileTree<double>::AddEntry, py::arg("entry"));
  py_class.def("reset", &dp::QuantileTree<double>::Reset);
  py_class.def("serialize", [](dp::QuantileTree<double>& obj) {
    differential_privacy::Summary to_return;
    to_return.mutable_data()->PackFrom(obj.Serialize());
    return to_return;
  });
  py_class.def(
      "merge",
      [](dp::QuantileTree<double>& tree, const dp::Summary& summary) {
        if (!summary.has_data()) {
          throw std::runtime_error("Cannot merge summary, no data.");
        }

        dp::BoundedQuantilesSummary quantiles_summary;
        if (!summary.data().UnpackTo(&quantiles_summary)) {
          throw std::runtime_error("Fail to upack data");
        }
        tree.Merge(quantiles_summary);
      },
      py::arg("summary"));

  py_class.def(
      "compute_quantiles",
      [](dp::QuantileTree<double>& tree, double epsilon, double delta,
         int max_partitions_contributed, int max_contributions_per_partition,
         const std::vector<double>& quantiles, const std::string& noise_type) {
        dp::QuantileTree<double>::Privatized privatized_tree =
            GetPrivatizeTree(tree, epsilon, delta, max_partitions_contributed,
                             max_contributions_per_partition, noise_type);

        std::vector<double> output;
        for (double quantile : quantiles) {
          auto result = privatized_tree.GetQuantile(quantile);
          if (result.ok())
            output.push_back(result.value());
          else
            output.push_back(std::nan(""));
        }
        return output;
      },
      py::arg("epsilon"), py::arg("delta"), py::arg("max_partitions_contributed"),
      py::arg("max_contributions_per_partition"), py::arg("quantiles"),
      py::arg("noise_type") = "laplace", "Compute multiple quantiles.");

  py_class.def(
      "compute_quantiles_and_confidence_intervals",
      [](dp::QuantileTree<double>& tree, double epsilon, double delta,
         int max_contributions_per_partition, int max_partitions_contributed,
         const std::vector<double>& quantiles, double confidence_interval_level,
         const std::string& noise_type) {
        dp::QuantileTree<double>::Privatized privatized_tree =
            GetPrivatizeTree(tree, epsilon, delta, max_partitions_contributed,
                             max_contributions_per_partition, noise_type);

        std::vector<QuantileConfidenceInterval> output;
        for (double quantile : quantiles) {
          auto status_ok_quantile = privatized_tree.GetQuantile(quantile);
          double result_quantile =
              status_ok_quantile.ok() ? status_ok_quantile.value() : std::nan("");

          auto status_or_interval = privatized_tree.ComputeNoiseConfidenceInterval(
              quantile, confidence_interval_level);

          double lower_bound = std::nan(""), upper_bound = std::nan("");
          if (status_or_interval.ok()) {
            lower_bound = status_or_interval.value().lower_bound();
            upper_bound = status_or_interval.value().upper_bound();
          }
          output.push_back({result_quantile, lower_bound, upper_bound});
        }
        return output;
      },
      py::arg("epsilon"), py::arg("delta"), py::arg("max_partitions_contributed"),
      py::arg("max_contributions_per_partition"), py::arg("quantiles"),
      py::arg("confidence_interval_level"), py::arg("noise_type") = "laplace",
      "Compute multiple quantiles and confidence intervals for them.");

  py_class.attr("__module__") = "_algorithms";
}

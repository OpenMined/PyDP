#ifndef PYDP_LIB_ALGORITHM_H_
#define PYDP_LIB_ALGORITHM_H_

#include "algorithms/algorithm.h"
#include "algorithms/bounded-mean.h"
#include "algorithms/bounded-standard-deviation.h"
#include "algorithms/bounded-sum.h"
#include "algorithms/bounded-variance.h"
#include "algorithms/count.h"
#include "algorithms/numerical-mechanisms.h"
#include "base/statusor.h"

namespace dp = differential_privacy;
namespace py = pybind11;

namespace differential_privacy {
namespace python {

template <typename T, class Algorithm>
constexpr bool is_bounded_algorithm() {
  return std::is_same<Algorithm, dp::BoundedMean<T>>::value ||
         std::is_same<Algorithm, dp::BoundedSum<T>>::value ||
         std::is_same<Algorithm, dp::BoundedStandardDeviation<T>>::value ||
         std::is_same<Algorithm, dp::BoundedVariance<T>>::value;
}

template <typename T, class Algorithm>
class AlgorithmBuilder {
 public:
  std::unique_ptr<Algorithm> build(double epsilon,
                                  //  std::optional<double> delta = std::nullopt,
                                   std::optional<T> lower_bound = std::nullopt,
                                   std::optional<T> upper_bound = std::nullopt,
                                   std::optional<int> l0_sensitivity = std::nullopt,
                                   std::optional<int> linf_sensitivity = std::nullopt) {
    auto builder = typename Algorithm::Builder();

    builder.SetEpsilon(epsilon);

    // if (delta.has_value()) builder.SetDelta(delta.value());
    if (l0_sensitivity.has_value())
      builder.SetMaxPartitionsContributed(l0_sensitivity.value());
    if (linf_sensitivity.has_value())
      builder.SetMaxContributionsPerPartition(linf_sensitivity.value());

    if constexpr (is_bounded_algorithm<T, Algorithm>()) {
      if (lower_bound.has_value()) builder.SetLower(lower_bound.value());
      if (upper_bound.has_value()) builder.SetUpper(upper_bound.value());
    }

    base::StatusOr<std::unique_ptr<Algorithm>> obj = builder.Build();
    if (!obj.ok()) {
      throw std::runtime_error(obj.status().error_message());
    }

    return std::move(obj.ValueOrDie());
  }

  std::map<std::type_index, std::string> type_to_name = {{typeid(double), "Double"},
                                                         {typeid(int), "Int"}};
  std::map<std::type_index, std::string> algorithm_to_name = {
      {typeid(dp::BoundedMean<T>), "BoundedMean"},
      {typeid(dp::BoundedSum<T>), "BoundedSum"},
      {typeid(dp::BoundedStandardDeviation<T>), "BoundedStandardDeviation"},
      {typeid(dp::BoundedVariance<T>), "BoundedVariance"},
      {typeid(dp::Count<T>), "Count"}};

  std::string get_algorithm_name() {
    // Set the suffix string
    return (algorithm_to_name[typeid(Algorithm)] + type_to_name[typeid(T)]);
  }

  void declare(py::module& m) {
    py::class_<Algorithm> pyself(m, get_algorithm_name().c_str());

    pyself.attr("__module__") = "_algorithms";

    // Constructors
    if constexpr (is_bounded_algorithm<T, Algorithm>()) {
      // Explicit bounds constructor
      pyself.def(
          py::init([this](double epsilon, T lower_bound, T upper_bound,
                          int l0_sensitivity, int linf_sensitivity) {
            return this->build(epsilon, lower_bound, upper_bound, l0_sensitivity,
                               linf_sensitivity);
          }),
          py::arg("epsilon"), py::arg("lower_bound"),
          py::arg("upper_bound"), py::arg("l0_sensitivity") = 1,
          py::arg("linf_sensitivity") = 1);
    }

    // No bounds constructor
    pyself.def(py::init([this](double epsilon, int l0_sensitivity,
                               int linf_sensitivity) {
                 return this->build(epsilon, std::nullopt /*lower_bound*/,
                                    std::nullopt /*upper_bound*/, l0_sensitivity,
                                    linf_sensitivity);
               }),
               py::arg("epsilon"), py::arg("l0_sensitivity") = 1,
               py::arg("linf_sensitivity") = 1);

    // Getters
    pyself.def_property_readonly("epsilon", &Algorithm::GetEpsilon);

    pyself.def("privacy_budget_left", &Algorithm::RemainingPrivacyBudget);

    pyself.def("consume_privacy_budget", &Algorithm::ConsumePrivacyBudget);

    pyself.def("memory_used", &Algorithm::MemoryUsed);

    // Input data
    pyself.def("add_entries", [](Algorithm& pythis, std::vector<T>& v) {
      pythis.AddEntries(v.begin(), v.end());
    });

    pyself.def("add_entry", &Algorithm::AddEntry);

    // Compute results
    pyself.def("result", [](Algorithm& pythis, std::vector<T>& v) {
      auto result = pythis.Result(v.begin(), v.end());

      if (!result.ok()) {
        throw std::runtime_error(result.status().error_message());
      }

      return dp::GetValue<double>(result.ValueOrDie());
    });

    pyself.def("partial_result", [](Algorithm& pythis) {
      auto result = pythis.PartialResult();

      if (!result.ok()) {
        throw std::runtime_error(result.status().error_message());
      }

      return dp::GetValue<double>(result.ValueOrDie());
    });

    pyself.def("partial_result", [](Algorithm& pythis, double privacy_budget) {
      if (privacy_budget > pythis.RemainingPrivacyBudget()) {
        throw std::runtime_error("Privacy budget requeted exceeds set privacy budget");
      }

      auto result = pythis.PartialResult(privacy_budget);

      if (!result.ok()) {
        throw std::runtime_error(result.status().error_message());
      }

      return dp::GetValue<double>(result.ValueOrDie());
    });

    pyself.def("partial_result", [](Algorithm& pythis, double privacy_budget,
                                    double noise_interval_level) {
      if (privacy_budget > pythis.RemainingPrivacyBudget()) {
        throw std::runtime_error("Privacy budget requeted exceeds set privacy budget");
      }

      auto result = pythis.PartialResult(privacy_budget, noise_interval_level);

      if (!result.ok()) {
        throw std::runtime_error(result.status().error_message());
      }

      return dp::GetValue<double>(result.ValueOrDie());
    });

    // Other methods
    pyself.def("consume_privacy_budget", &Algorithm::ConsumePrivacyBudget);

    pyself.def("reset", &Algorithm::Reset);

    pyself.def("serialize", &Algorithm::Serialize);

    pyself.def("merge", &Algorithm::Merge);

    pyself.def("noise_confidence_interval", &Algorithm::NoiseConfidenceInterval);
  }
};

}  // namespace python
}  // namespace differential_privacy

#endif  // PYDP_LIB_ALGORITHM_H_

#ifndef PYDP_LIB_ALGORITHM_H_
#define PYDP_LIB_ALGORITHM_H_

#include "absl/status/statusor.h"
#include "algorithms/algorithm.h"
#include "algorithms/bounded-mean.h"
#include "algorithms/bounded-standard-deviation.h"
#include "algorithms/bounded-sum.h"
#include "algorithms/bounded-variance.h"
#include "algorithms/count.h"
#include "algorithms/numerical-mechanisms.h"
#include "algorithms/order-statistics.h"
#include "proto/summary.pb.h"

namespace dp = differential_privacy;
namespace py = pybind11;

namespace differential_privacy {
namespace python {

template <typename T, class Algorithm>
constexpr bool is_bounded_algorithm() {
  return std::is_same<Algorithm, dp::BoundedMean<T>>::value ||
         std::is_same<Algorithm, dp::BoundedSum<T>>::value ||
         std::is_same<Algorithm, dp::BoundedStandardDeviation<T>>::value ||
         std::is_same<Algorithm, dp::BoundedVariance<T>>::value ||
         std::is_same<Algorithm, dp::continuous::Max<T>>::value ||
         std::is_same<Algorithm, dp::continuous::Min<T>>::value ||
         std::is_same<Algorithm, dp::continuous::Median<T>>::value ||
         std::is_same<Algorithm, dp::continuous::Percentile<T>>::value;
}

template <typename T, class Algorithm>
constexpr bool is_percentile() {
  return std::is_same<Algorithm, dp::continuous::Percentile<T>>::value;
}

template <typename T, class Algorithm>
constexpr bool should_return_T() {
  return std::is_same<Algorithm, dp::continuous::Max<T>>::value ||
         std::is_same<Algorithm, dp::continuous::Min<T>>::value ||
         std::is_same<Algorithm, dp::continuous::Median<T>>::value ||
         std::is_same<Algorithm, dp::BoundedSum<T>>::value;
}

template <typename T, class Algorithm>
constexpr bool should_return_double() {
  return std::is_same<Algorithm, dp::BoundedMean<T>>::value ||
         std::is_same<Algorithm, dp::BoundedStandardDeviation<T>>::value ||
         std::is_same<Algorithm, dp::BoundedVariance<T>>::value ||
         std::is_same<Algorithm, dp::continuous::Percentile<T>>::value;
}

template <typename T, class Algorithm>
constexpr bool should_return_int() {
  return std::is_same<Algorithm, dp::Count<T>>::value;
}

template <typename T, class Algorithm>
class AlgorithmBuilder {
 public:
  std::unique_ptr<Algorithm> build(double epsilon, double delta,
                                   std::optional<double> percentile = std::nullopt,
                                   std::optional<T> lower_bound = std::nullopt,
                                   std::optional<T> upper_bound = std::nullopt,
                                   std::optional<int> l0_sensitivity = std::nullopt,
                                   std::optional<int> linf_sensitivity = std::nullopt) {
    auto builder = typename Algorithm::Builder();

    if constexpr (is_percentile<T, Algorithm>()) {
      if (percentile.has_value()) builder.SetPercentile(percentile.value());
    }

    builder.SetEpsilon(epsilon);

    builder.SetDelta(delta);

    if (l0_sensitivity.has_value())
      builder.SetMaxPartitionsContributed(l0_sensitivity.value());
    if (linf_sensitivity.has_value())
      builder.SetMaxContributionsPerPartition(linf_sensitivity.value());

    if constexpr (is_bounded_algorithm<T, Algorithm>()) {
      if (lower_bound.has_value()) builder.SetLower(lower_bound.value());
      if (upper_bound.has_value()) builder.SetUpper(upper_bound.value());
    }

    absl::StatusOr<std::unique_ptr<Algorithm>> obj = builder.Build();
    if (!obj.ok()) {
      throw std::runtime_error(obj.status().ToString());
    }

    return std::move(obj.value());
  }

  std::map<std::type_index, std::string> type_to_name = {
      {typeid(double), "Double"},
      {typeid(int), "Int"},
      {typeid(int64_t), "Int64"},
  };
  std::map<std::type_index, std::string> algorithm_to_name = {
      {typeid(dp::BoundedMean<T>), "BoundedMean"},
      {typeid(dp::BoundedSum<T>), "BoundedSum"},
      {typeid(dp::BoundedStandardDeviation<T>), "BoundedStandardDeviation"},
      {typeid(dp::BoundedVariance<T>), "BoundedVariance"},
      {typeid(dp::Count<T>), "Count"},
      {typeid(dp::continuous::Min<T>), "Min"},
      {typeid(dp::continuous::Max<T>), "Max"},
      {typeid(dp::continuous::Median<T>), "Median"},
      {typeid(dp::continuous::Percentile<T>), "Percentile"}

  };

  std::string get_algorithm_name() {
    // Set the suffix string
    return (algorithm_to_name[typeid(Algorithm)] + type_to_name[typeid(T)]);
  }

  void declare(py::module& m) {
    py::class_<Algorithm> pyself(m, get_algorithm_name().c_str());

    pyself.attr("__module__") = "_algorithms";

    // Constructors
    if constexpr (is_bounded_algorithm<T, Algorithm>()) {
      if constexpr (is_percentile<T, Algorithm>()) {
        // Explicit percentile constructor
        pyself.def(py::init([this](double epsilon, double delta, double percentile,
                                   T lower_bound, T upper_bound, int l0_sensitivity,
                                   int linf_sensitivity) {
                     return this->build(epsilon, delta, percentile, lower_bound,
                                        upper_bound, l0_sensitivity, linf_sensitivity);
                   }),
                   py::arg("epsilon"), py::arg("delta") = 0, py::arg("percentile"),
                   py::arg("lower_bound"), py::arg("upper_bound"),
                   py::arg("l0_sensitivity") = 1, py::arg("linf_sensitivity") = 1);
      }
      // Explicit bounds constructor
      pyself.def(
          py::init([this](double epsilon, double delta, T lower_bound, T upper_bound,
                          int l0_sensitivity, int linf_sensitivity) {
            return this->build(epsilon, delta, std::nullopt /*percentile*/, lower_bound,
                               upper_bound, l0_sensitivity, linf_sensitivity);
          }),
          py::arg("epsilon"), py::arg("delta") = 0, py::arg("lower_bound"),
          py::arg("upper_bound"), py::arg("l0_sensitivity") = 1,
          py::arg("linf_sensitivity") = 1);
    }

    // No bounds constructor
    pyself.def(py::init([this](double epsilon, double delta, int l0_sensitivity,
                               int linf_sensitivity) {
                 return this->build(epsilon, delta, std::nullopt /*percentile*/,
                                    std::nullopt /*lower_bound*/,
                                    std::nullopt /*upper_bound*/, l0_sensitivity,
                                    linf_sensitivity);
               }),
               py::arg("epsilon"), py::arg("delta") = 0, py::arg("l0_sensitivity") = 1,
               py::arg("linf_sensitivity") = 1);

    // Getters
    pyself.def_property_readonly("epsilon", &Algorithm::GetEpsilon);
    pyself.def_property_readonly("delta", &Algorithm::GetDelta);

    pyself.def("memory_used", &Algorithm::MemoryUsed);

    // Input data
    pyself.def("add_entries", [](Algorithm& pythis, std::vector<T>& v) {
      pythis.AddEntries(v.begin(), v.end());
    });

    pyself.def("add_entry", &Algorithm::AddEntry);

    // // Compute results
    pyself.def("result", [](Algorithm& pythis, std::vector<T>& v) {
      auto result = pythis.Result(v.begin(), v.end());

      if (!result.ok()) {
        throw std::runtime_error(result.status().ToString());
      }
      if constexpr ((should_return_T<T, Algorithm>()))
        return dp::GetValue<T>(result.value());
      if constexpr ((should_return_double<T, Algorithm>()))
        return dp::GetValue<double>(result.value());
      if constexpr ((should_return_int<T, Algorithm>()))
        return dp::GetValue<int64_t>(result.value());
    });

    pyself.def("partial_result", [](Algorithm& pythis) {
      auto result = pythis.PartialResult();

      if (!result.ok()) {
        throw std::runtime_error(result.status().ToString());
      }

      if constexpr ((should_return_T<T, Algorithm>()))
        return dp::GetValue<T>(result.value());
      if constexpr ((should_return_double<T, Algorithm>()))
        return dp::GetValue<double>(result.value());
      if constexpr ((should_return_int<T, Algorithm>()))
        return dp::GetValue<int64_t>(result.value());
    });

    pyself.def("partial_result", [](Algorithm& pythis, double privacy_budget) {
      auto result = pythis.PartialResult(privacy_budget);

      if (!result.ok()) {
        throw std::runtime_error(result.status().ToString());
      }

      if constexpr ((should_return_T<T, Algorithm>()))
        return dp::GetValue<T>(result.value());
      if constexpr ((should_return_double<T, Algorithm>()))
        return dp::GetValue<double>(result.value());
      if constexpr ((should_return_int<T, Algorithm>()))
        return dp::GetValue<int64_t>(result.value());
    });

    pyself.def("partial_result", [](Algorithm& pythis, double noise_interval_level) {
      auto result = pythis.PartialResult(noise_interval_level);

      if (!result.ok()) {
        throw std::runtime_error(result.status().ToString());
      }
      if constexpr ((should_return_T<T, Algorithm>()))
        return dp::GetValue<T>(result.value());
      if constexpr ((should_return_double<T, Algorithm>()))
        return dp::GetValue<double>(result.value());
      if constexpr ((should_return_int<T, Algorithm>()))
        return dp::GetValue<int64_t>(result.value());
    });

    // Other methods
    pyself.def("reset", &Algorithm::Reset);

    pyself.def("serialize", &Algorithm::Serialize);

    pyself.def("merge", [](Algorithm& pythis, const dp::Summary& summary) {
      auto status = pythis.Merge(summary);
      if (!status.ok()) {
        throw std::runtime_error(status.ToString());
      }
    });

    pyself.def("noise_confidence_interval", &Algorithm::NoiseConfidenceInterval);

    // Percentile special case.
    if constexpr (is_percentile<T, Algorithm>()) {
      pyself.def_property_readonly("percentile", &Algorithm::GetPercentile);
    }
  }
};

}  // namespace python
}  // namespace differential_privacy

#endif  // PYDP_LIB_ALGORITHM_H_

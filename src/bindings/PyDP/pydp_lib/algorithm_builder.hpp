#ifndef PYDP_LIB_ALGORITHM_H_
#define PYDP_LIB_ALGORITHM_H_

#include "algorithms/algorithm.h"
#include "algorithms/bounded-mean.h"
#include "algorithms/bounded-standard-deviation.h"
#include "algorithms/bounded-sum.h"
#include "algorithms/bounded-variance.h"
#include "algorithms/numerical-mechanisms.h"
#include "base/statusor.h"

namespace dp = differential_privacy;

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
  std::unique_ptr<Algorithm> Build(double epsilon,
                                   std::optional<T> lower_bound = std::nullopt,
                                   std::optional<T> upper_bound = std::nullopt,
                                   std::optional<int> l0_sensitivity = std::nullopt,
                                   std::optional<int> linf_sensitivity = std::nullopt) {
    auto builder = typename Algorithm::Builder();

    builder.SetEpsilon(epsilon);

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
      {typeid(dp::BoundedVariance<T>), "BoundedVariance"}};

  std::string get_algorithm_name() {
    // Set the suffix string
    return (algorithm_to_name[typeid(Algorithm)] + type_to_name[typeid(T)]);
  }
};

}  // namespace python
}  // namespace differential_privacy

#endif  // PYDP_LIB_ALGORITHM_H_

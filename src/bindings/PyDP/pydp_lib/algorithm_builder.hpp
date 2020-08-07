#ifndef PYDP_LIB_ALGORITHM_H_
#define PYDP_LIB_ALGORITHM_H_

#include "algorithms/algorithm.h"
#include "algorithms/bounded-mean.h"
#include "algorithms/bounded-standard-deviation.h"
#include "algorithms/bounded-sum.h"
#include "algorithms/bounded-variance.h"
#include "algorithms/numerical-mechanisms.h"

namespace dp = differential_privacy;

namespace differential_privacy {
namespace python {

template <typename T, class Algorithm>
class AlgorithmBuilder {
 public:
  std::unique_ptr<Algorithm> Build(double epsilon) {
    return typename Algorithm::Builder()
        .SetLaplaceMechanism(absl::make_unique<LaplaceMechanism::Builder>())
        .SetEpsilon(epsilon)
        .Build()
        .ValueOrDie();
  }

  std::unique_ptr<Algorithm> BuildWithBounds(double epsilon, T lower_bound,
                                             T upper_bound, int l0_sensitivity = 1,
                                             int linf_sensitivity = 1) {
    return typename Algorithm::Builder()
        .SetLaplaceMechanism(absl::make_unique<LaplaceMechanism::Builder>())
        .SetEpsilon(epsilon)
        .SetLower(lower_bound)
        .SetUpper(upper_bound)
        .SetMaxPartitionsContributed(l0_sensitivity)
        .SetMaxContributionsPerPartition(linf_sensitivity)
        .Build()
        .ValueOrDie();
  }

  std::unique_ptr<Algorithm> BuildWithoutBounds(double epsilon, int l0_sensitivity = 1,
                                                int linf_sensitivity = 1) {
    return typename Algorithm::Builder()
        .SetLaplaceMechanism(absl::make_unique<LaplaceMechanism::Builder>())
        .SetEpsilon(epsilon)
        .SetMaxPartitionsContributed(l0_sensitivity)
        .SetMaxContributionsPerPartition(linf_sensitivity)
        .Build()
        .ValueOrDie();
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

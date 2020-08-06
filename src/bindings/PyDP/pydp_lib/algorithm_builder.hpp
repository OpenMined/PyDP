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

  std::string get_algorithm_name() {
    // Set the suffix string
    std::string suffix = "";
    // TODO: Change to mapping function
    if (typeid(T) == typeid(int)) {
      suffix = "Int";
    } else if (typeid(T) == typeid(double)) {
      suffix = "Double";
    } else {
      throw std::runtime_error("Binding error - Only int and double types supported");
    }

    // Set the algorithm name string
    std::string name = "";
    // TODO: Change to mapping function
    if (typeid(Algorithm) == typeid(dp::BoundedMean<T>)) {
      name = "BoundedMean";
    } else if (typeid(Algorithm) == typeid(dp::BoundedSum<T>)) {
      name = "BoundedSum";
    } else if (typeid(Algorithm) == typeid(dp::BoundedStandardDeviation<T>)) {
      name = "BoundedStandardDeviation";
    } else if (typeid(Algorithm) == typeid(dp::BoundedVariance<T>)) {
      name = "BoundedVariance";
    } else {
      throw std::runtime_error(std::string("Binding error - Unsupported algorithm: ") +
                               std::string(typeid(Algorithm).name()));
    }
    return (name + suffix);
  }
};

}  // namespace python
}  // namespace differential_privacy

#endif  // PYDP_LIB_ALGORITHM_H_

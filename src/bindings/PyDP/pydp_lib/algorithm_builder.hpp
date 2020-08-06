#ifndef PYDP_LIB_ALGORITHM_H_
#define PYDP_LIB_ALGORITHM_H_

#include "algorithms/algorithm.h"
#include "algorithms/numerical-mechanisms.h"

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
};

}  // namespace python
}  // namespace differential_privacy

#endif  // PYDP_LIB_ALGORITHM_H_

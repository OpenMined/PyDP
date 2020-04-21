#include "c_api.h"

#include "differential_privacy/algorithms/bounded-mean.h"

extern "C" {

double DP_NewBoundedMeanIntResult(DP_BoundedMeanInt* config, int begin,
                                  int end) {
  std::unique_ptr<BoundedMean<Int>> mean = typename BoundedMean<Int>::Builder()
                                               .SetEpsilon(config->epsilon)
                                               .SetLower(config->lower)
                                               .SetUpper(config->upper)
                                               .Build()
                                               .ValueOrDie();

  return GetValue<double>(mean->Result(being, end.ValueOrDie());
}

DP_BoundedMeanInt* DP_NewBoundedMeanInt_Build(double* epsilon, int* lower,
                                              int* upper) {
  return new DP_BoundedMeanInt { epsilon, lower, upper }
}

}  // end extern "C"

#include "c_api.h"

#include "differential_privacy/algorithms/bounded-mean.h"

extern "C" {
namespace differential_privacy {

double DP_NewBoundedMeanIntResult(DP_BoundedMeanInt* config, int begin,
                                  int end) {
  std::unique_ptr<BoundedMean<int>> mean = BoundedMean<int>::Builder()
                                               .SetEpsilon(config->epsilon)
                                               .SetLower(config->lower)
                                               .SetUpper(config->upper)
                                               .Build()
                                               .ValueOrDie();

  Output result = mean->Result(&begin, &end).ValueOrDie();
  return GetValue<double>(result);
}

DP_BoundedMeanInt* DP_NewBoundedMeanInt_Build(double epsilon, int lower,
                                              int upper) {
  return new DP_BoundedMeanInt { epsilon, lower, upper };
}

void DP_DeleteBoundedMeanInt(DP_BoundedMeanInt* config){
  delete config;
};

}  // end namespace differential_privacy
}  // end extern "C"

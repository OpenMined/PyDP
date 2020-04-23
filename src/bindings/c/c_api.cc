#include "c_api.h"

#include "pybind11/pybind11.h"
#include "differential_privacy/algorithms/bounded-mean.h"

extern "C" {
namespace differential_privacy {

double DP_ResultBoundedMeanInt(DP_BoundedMeanInt* config, pybind11::list l) {
  std::vector<int> a;
  
  for (auto i : l){
    a.push_back(i.cast<int>());
  }

  std::unique_ptr<BoundedMean<int>> mean = BoundedMean<int>::Builder()
                                               .SetEpsilon(config->epsilon)
                                               .SetLower(config->lower)
                                               .SetUpper(config->upper)
                                               .Build()
                                               .ValueOrDie();

  Output result = mean->Result(a.begin(), a.end()).ValueOrDie();

  return GetValue<double>(result);
}

DP_BoundedMeanInt* DP_NewBoundedMeanInt(double epsilon, int lower, int upper) {
  return new DP_BoundedMeanInt { epsilon, lower, upper };
}

void DP_DeleteBoundedMeanInt(DP_BoundedMeanInt* config){
  delete config;
};

}  // end namespace differential_privacy
}  // end extern "C"

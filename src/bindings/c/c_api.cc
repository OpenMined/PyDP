#include "c_api.h"

#include "differential_privacy/algorithms/bounded-mean.h"
#include "pybind11/pybind11.h"

extern "C" {
namespace differential_privacy {

bool has_bounds;

double DP_ResultBoundedMean(DP_BoundedMeanInt* config, pybind11::list l) {
  std::vector<double> a;

  for (auto i : l) {
    a.push_back(i.cast<double>());
  }
  std::unique_ptr<BoundedMean<double>> mean;
  if (has_bounds) {
    mean = BoundedMean<double>::Builder()
               .SetEpsilon(config->epsilon)
               .SetLower(config->lower)
               .SetUpper(config->upper)
               .Build()
               .ValueOrDie();
  } else {
    mean =
        BoundedMean<double>::Builder().SetEpsilon(config->epsilon).Build().ValueOrDie();
  }
  Output result = mean->Result(a.begin(), a.end()).ValueOrDie();

  return GetValue<double>(result);
}

DP_BoundedMeanInt* DP_NewBoundedMean(double epsilon, int lower, int upper) {
  has_bounds = true;
  return new DP_BoundedMeanInt{epsilon, lower, upper};
}

DP_BoundedMeanInt* DP_NewBoundedMean1(double epsilon) {
  has_bounds = false;
  return new DP_BoundedMeanInt{epsilon};
}

void DP_DeleteBoundedMean(DP_BoundedMeanInt* config) {
  delete config;
};

}  // end namespace differential_privacy
}  // end extern "C"

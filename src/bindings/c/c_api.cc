#include "c_api.h"

#include "differential_privacy/algorithms/algorithm.h"

#include "differential_privacy/algorithms/bounded-mean.h"

#include "absl/random/distributions.h"
#include "differential_privacy/algorithms/order-statistics.h"

#include "pybind11/pybind11.h"

extern "C" {
namespace differential_privacy {

// Helper variable in-case bounds are not set
bool has_bounds;

// Bounded Mean
double Result_BoundedMean(BoundedFunctionHelperObject* config, pybind11::list l) {
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

// Order Statistics

// Max

int64_t Result_Max(BoundedFunctionHelperObject* config, pybind11::list l,
                   double privacy_budget) {
  std::unique_ptr<continuous::Max<int64_t>> search;
  if (has_bounds) {
    search = continuous::Max<int64_t>::Builder()
                 .SetEpsilon(config->epsilon)
                 .SetLower(config->lower)
                 .SetUpper(config->upper)
                 .Build()
                 .ValueOrDie();
  } else {
    search = continuous::Max<int64_t>::Builder()
                 .SetEpsilon(config->epsilon)
                 .Build()
                 .ValueOrDie();
  }

  for (auto i : l) {
    search->AddEntry(i.cast<double>());
  }

  return GetValue<int64_t>(search->PartialResult(privacy_budget).ValueOrDie());
}

// Min

int64_t Result_Min(BoundedFunctionHelperObject* config, pybind11::list l,
                   double privacy_budget) {
  std::unique_ptr<continuous::Min<int64_t>> search;
  if (has_bounds) {
    search = continuous::Min<int64_t>::Builder()
                 .SetEpsilon(config->epsilon)
                 .SetLower(config->lower)
                 .SetUpper(config->upper)
                 .Build()
                 .ValueOrDie();
  } else {
    search = continuous::Min<int64_t>::Builder()
                 .SetEpsilon(config->epsilon)
                 .Build()
                 .ValueOrDie();
  }

  for (auto i : l) {
    search->AddEntry(i.cast<double>());
  }

  return GetValue<int64_t>(search->PartialResult(privacy_budget).ValueOrDie());
}

// Max

int64_t Result_Median(BoundedFunctionHelperObject* config, pybind11::list l,
                      double privacy_budget) {
  std::unique_ptr<continuous::Median<int64_t>> search;
  if (has_bounds) {
    search = continuous::Median<int64_t>::Builder()
                 .SetEpsilon(config->epsilon)
                 .SetLower(config->lower)
                 .SetUpper(config->upper)
                 .Build()
                 .ValueOrDie();
  } else {
    search = continuous::Median<int64_t>::Builder()
                 .SetEpsilon(config->epsilon)
                 .Build()
                 .ValueOrDie();
  }

  for (auto i : l) {
    search->AddEntry(i.cast<double>());
  }

  return GetValue<int64_t>(search->PartialResult(privacy_budget).ValueOrDie());
}

// Percentile

int64_t Result_Percentile(BoundedFunctionHelperObject* config, pybind11::list l,
                          double privacy_budget, double percentile) {
  std::unique_ptr<continuous::Percentile<int64_t>> search;
  if (has_bounds) {
    search = continuous::Percentile<int64_t>::Builder()
                 .SetPercentile(percentile)
                 .SetEpsilon(config->epsilon)
                 .SetLower(config->lower)
                 .SetUpper(config->upper)
                 .Build()
                 .ValueOrDie();
  } else {
    search = continuous::Percentile<int64_t>::Builder()
                 .SetPercentile(percentile)
                 .SetEpsilon(config->epsilon)
                 .Build()
                 .ValueOrDie();
  }

  for (auto i : l) {
    search->AddEntry(i.cast<double>());
  }

  return GetValue<int64_t>(search->PartialResult(privacy_budget).ValueOrDie());
}

// Common functions

BoundedFunctionHelperObject* NewBoundedFunctionObject(double epsilon, int lower,
                                                      int upper) {
  has_bounds = true;
  return new BoundedFunctionHelperObject{epsilon, lower, upper};
}

BoundedFunctionHelperObject* NewBoundedFunctionObject1(double epsilon) {
  has_bounds = false;
  return new BoundedFunctionHelperObject{epsilon};
}

void DeleteBoundedFunctionObject(BoundedFunctionHelperObject* config) {
  delete config;
};

}  // end namespace differential_privacy
}  // end extern "C"

#include "c_api.h"

#include "algorithms/algorithm.h"

#include "algorithms/bounded-mean.h"
#include "algorithms/bounded-standard-deviation.h"
#include "algorithms/bounded-sum.h"
#include "algorithms/bounded-variance.h"

#include "absl/random/distributions.h"
#include "algorithms/order-statistics.h"

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
  base::StatusOr<std::unique_ptr<BoundedMean<double>>> mean_obj;
  if (has_bounds) {
     mean_obj = BoundedMean<double>::Builder()
               .SetEpsilon(config->epsilon)
               .SetLower(config->lower)
               .SetUpper(config->upper)
               .Build();
  } else {
    // TODO: a better solution to this is needed similar to ASSIGN_OR_RETURN but with a raised exeception
    mean_obj = BoundedMean<double>::Builder().SetEpsilon(config->epsilon).Build();
  }
    
  if (!mean_obj.ok()){
     // TODO: custtom error?
    throw std::runtime_error(mean_obj.status().error_message());
  }

  base::StatusOr<Output> resultf = mean_obj.ValueOrDie()->Result(a.begin(), a.end());
  if (resultf.ok()){
    return GetValue<double>(resultf.ValueOrDie());
  }
  else{
    throw std::runtime_error(resultf.status().error_message());
  }
}

// Bounded Sum
double Result_BoundedSum(BoundedFunctionHelperObject* config, pybind11::list l) {
  std::vector<double> a;

  for (auto i : l) {
    a.push_back(i.cast<double>());
  }
  base::StatusOr<std::unique_ptr<BoundedSum<double>>> sum_obj;
  if (has_bounds) {
     sum_obj = BoundedSum<double>::Builder()
               .SetEpsilon(config->epsilon)
               .SetLower(config->lower)
               .SetUpper(config->upper)
               .Build();
  } else {
    // TODO: a better solution to this is needed similar to ASSIGN_OR_RETURN but with a raised exeception
    sum_obj = BoundedSum<double>::Builder().SetEpsilon(config->epsilon).Build();
  }
    
  if (!sum_obj.ok()){
    throw std::runtime_error(sum_obj.status().error_message());
  }

  base::StatusOr<Output> resultf = sum_obj.ValueOrDie()->Result(a.begin(), a.end());
  if (resultf.ok()){
    return GetValue<double>(resultf.ValueOrDie());
  }
  else{
    throw std::runtime_error(resultf.status().error_message());
  }
}

double Result_BoundedStandardDeviation(BoundedFunctionHelperObject* config,
                                       pybind11::list l) {
  std::vector<double> a;

  for (auto i : l) {
    a.push_back(i.cast<double>());
  }
  base::StatusOr<std::unique_ptr<BoundedStandardDeviation<double>>> sd_obj;
  if (has_bounds) {
     sd_obj = BoundedStandardDeviation<double>::Builder()
               .SetEpsilon(config->epsilon)
               .SetLower(config->lower)
               .SetUpper(config->upper)
               .Build();
  } else {
    // TODO: a better solution to this is needed similar to ASSIGN_OR_RETURN but with a raised exeception
    sd_obj = BoundedStandardDeviation<double>::Builder().SetEpsilon(config->epsilon).Build();
  }
    
  if (!sd_obj.ok()){
    throw std::runtime_error(sd_obj.status().error_message());
  }

  base::StatusOr<Output> resultf = sd_obj.ValueOrDie()->Result(a.begin(), a.end());
  if (resultf.ok()){
    return GetValue<double>(resultf.ValueOrDie());
  }
  else{
    throw std::runtime_error(resultf.status().error_message());
  }
}

double Result_BoundedVariance(BoundedFunctionHelperObject* config, pybind11::list l) {
  std::vector<double> a;

  for (auto i : l) {
    a.push_back(i.cast<double>());
  }
  base::StatusOr<std::unique_ptr<BoundedVariance<double>>> variance_obj;
  if (has_bounds) {
     variance_obj = BoundedVariance<double>::Builder()
               .SetEpsilon(config->epsilon)
               .SetLower(config->lower)
               .SetUpper(config->upper)
               .Build();
  } else {
    // TODO: a better solution to this is needed similar to ASSIGN_OR_RETURN but with a raised exeception
    variance_obj = BoundedVariance<double>::Builder().SetEpsilon(config->epsilon).Build();
  }
    
  if (!variance_obj.ok()){
    throw std::runtime_error(variance_obj.status().error_message());
  }
  else{
    base::StatusOr<Output> resultf = variance_obj.ValueOrDie()->Result(a.begin(), a.end());
    if (resultf.ok()){
      return GetValue<double>(resultf.ValueOrDie());
    }
    else{
      throw std::runtime_error(resultf.status().error_message());
    }
  }
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

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
int l0_sensitivity = 1;
int linf_sensitivity = 1;

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
                   .SetLower(config->lower_bound)
                   .SetUpper(config->upper_bound)
                   .SetMaxPartitionsContributed(l0_sensitivity)
                   .SetMaxContributionsPerPartition(linf_sensitivity)
                   .Build();
  } else {
    // TODO: a better solution to this is needed similar to ASSIGN_OR_RETURN but with a
    // raised exeception
    mean_obj = BoundedMean<double>::Builder()
                   .SetEpsilon(config->epsilon)
                   .SetMaxPartitionsContributed(l0_sensitivity)
                   .SetMaxContributionsPerPartition(linf_sensitivity)
                   .Build();
  }

  if (!mean_obj.ok()) {
    // TODO: custtom error?
    throw std::runtime_error(mean_obj.status().error_message());
  }

  base::StatusOr<Output> resultf = mean_obj.ValueOrDie()->Result(a.begin(), a.end());
  if (resultf.ok()) {
    return GetValue<double>(resultf.ValueOrDie());
  } else {
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
                  .SetLower(config->lower_bound)
                  .SetUpper(config->upper_bound)
                  .SetMaxPartitionsContributed(l0_sensitivity)
                  .SetMaxContributionsPerPartition(linf_sensitivity)
                  .Build();
  } else {
    // TODO: a better solution to this is needed similar to ASSIGN_OR_RETURN but with a
    // raised exeception
    sum_obj = BoundedSum<double>::Builder()
                  .SetEpsilon(config->epsilon)
                  .SetMaxPartitionsContributed(l0_sensitivity)
                  .SetMaxContributionsPerPartition(linf_sensitivity)
                  .Build();
  }

  if (!sum_obj.ok()) {
    throw std::runtime_error(sum_obj.status().error_message());
  }

  base::StatusOr<Output> resultf = sum_obj.ValueOrDie()->Result(a.begin(), a.end());
  if (resultf.ok()) {
    return GetValue<double>(resultf.ValueOrDie());
  } else {
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
                 .SetLower(config->lower_bound)
                 .SetUpper(config->upper_bound)
                 .SetMaxPartitionsContributed(l0_sensitivity)
                 .SetMaxContributionsPerPartition(linf_sensitivity)
                 .Build();
  } else {
    // TODO: a better solution to this is needed similar to ASSIGN_OR_RETURN but with a
    // raised exeception
    sd_obj = BoundedStandardDeviation<double>::Builder()
                 .SetEpsilon(config->epsilon)
                 .SetMaxPartitionsContributed(l0_sensitivity)
                 .SetMaxContributionsPerPartition(linf_sensitivity)
                 .Build();
  }

  if (!sd_obj.ok()) {
    throw std::runtime_error(sd_obj.status().error_message());
  }

  base::StatusOr<Output> resultf = sd_obj.ValueOrDie()->Result(a.begin(), a.end());
  if (resultf.ok()) {
    return GetValue<double>(resultf.ValueOrDie());
  } else {
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
                       .SetLower(config->lower_bound)
                       .SetUpper(config->upper_bound)
                       .SetMaxPartitionsContributed(l0_sensitivity)
                       .SetMaxContributionsPerPartition(linf_sensitivity)
                       .Build();
  } else {
    variance_obj = BoundedVariance<double>::Builder()
                       .SetEpsilon(config->epsilon)
                       .SetMaxPartitionsContributed(l0_sensitivity)
                       .SetMaxContributionsPerPartition(linf_sensitivity)
                       .Build();
  }

  if (!variance_obj.ok()) {
    throw std::runtime_error(variance_obj.status().error_message());
  } else {
    base::StatusOr<Output> resultf =
        variance_obj.ValueOrDie()->Result(a.begin(), a.end());
    if (resultf.ok()) {
      return GetValue<double>(resultf.ValueOrDie());
    } else {
      throw std::runtime_error(resultf.status().error_message());
    }
  }
}

// Order Statistics

// Max

int64_t Result_Max(BoundedFunctionHelperObject* config, pybind11::list l,
                   double privacy_budget) {
  base::StatusOr<std::unique_ptr<continuous::Max<int64_t>>> max;
  if (has_bounds) {
    max = continuous::Max<int64_t>::Builder()
              .SetEpsilon(config->epsilon)
              .SetLower(config->lower_bound)
              .SetUpper(config->upper_bound)
              .SetMaxPartitionsContributed(l0_sensitivity)
              .SetMaxContributionsPerPartition(linf_sensitivity)
              .Build();
  } else {
    max = continuous::Max<int64_t>::Builder().SetEpsilon(config->epsilon).Build();
  }
  if (!max.ok()) {
    throw std::runtime_error(max.status().error_message());
  } else {
    for (auto i : l) {
      max.ValueOrDie()->AddEntry(i.cast<int64_t>());
    }
    base::StatusOr<Output> resultf = max.ValueOrDie()->PartialResult(privacy_budget);
    if (resultf.ok()) {
      return GetValue<int64_t>(resultf.ValueOrDie());
    } else {
      throw std::runtime_error(resultf.status().error_message());
    }
  }
}

// Min

int64_t Result_Min(BoundedFunctionHelperObject* config, pybind11::list l,
                   double privacy_budget) {
  base::StatusOr<std::unique_ptr<continuous::Min<int64_t>>> min;
  if (has_bounds) {
    min = continuous::Min<int64_t>::Builder()
              .SetEpsilon(config->epsilon)
              .SetLower(config->lower_bound)
              .SetUpper(config->upper_bound)
              .SetMaxPartitionsContributed(l0_sensitivity)
              .SetMaxContributionsPerPartition(linf_sensitivity)
              .Build();
  } else {
    min = continuous::Min<int64_t>::Builder()
              .SetEpsilon(config->epsilon)
              .SetMaxPartitionsContributed(l0_sensitivity)
              .SetMaxContributionsPerPartition(linf_sensitivity)
              .Build();
  }
  if (!min.ok()) {
    throw std::runtime_error(min.status().error_message());
  } else {
    for (auto i : l) {
      min.ValueOrDie()->AddEntry(i.cast<int64_t>());
    }
    base::StatusOr<Output> resultf = min.ValueOrDie()->PartialResult(privacy_budget);
    if (resultf.ok()) {
      return GetValue<int64_t>(resultf.ValueOrDie());
    } else {
      throw std::runtime_error(resultf.status().error_message());
    }
  }
}

// Max

int64_t Result_Median(BoundedFunctionHelperObject* config, pybind11::list l,
                      double privacy_budget) {
  base::StatusOr<std::unique_ptr<continuous::Median<int64_t>>> median;
  if (has_bounds) {
    median = continuous::Median<int64_t>::Builder()
                 .SetEpsilon(config->epsilon)
                 .SetLower(config->lower_bound)
                 .SetUpper(config->upper_bound)
                 .SetMaxPartitionsContributed(l0_sensitivity)
                 .SetMaxContributionsPerPartition(linf_sensitivity)
                 .Build();
  } else {
    median = continuous::Median<int64_t>::Builder()
                 .SetEpsilon(config->epsilon)
                 .SetMaxPartitionsContributed(l0_sensitivity)
                 .SetMaxContributionsPerPartition(linf_sensitivity)
                 .Build();
  }
  if (!median.ok()) {
    throw std::runtime_error(median.status().error_message());
  } else {
    for (auto i : l) {
      median.ValueOrDie()->AddEntry(i.cast<int64_t>());
    }
    base::StatusOr<Output> resultf = median.ValueOrDie()->PartialResult(privacy_budget);
    if (resultf.ok()) {
      return GetValue<int64_t>(resultf.ValueOrDie());
    } else {
      throw std::runtime_error(resultf.status().error_message());
    }
  }
}

// Percentile
// can't add error handling to this for some reasons
// TODO
int64_t Result_Percentile(BoundedFunctionHelperObject* config, pybind11::list l,
                          double privacy_budget, double percentile) {
  std::unique_ptr<continuous::Percentile<int64_t>> search;
  if (has_bounds) {
    search = continuous::Percentile<int64_t>::Builder()
                 .SetPercentile(percentile)
                 .SetEpsilon(config->epsilon)
                 .SetLower(config->lower_bound)
                 .SetUpper(config->upper_bound)
                 .SetMaxPartitionsContributed(l0_sensitivity)
                 .SetMaxContributionsPerPartition(linf_sensitivity)
                 .Build()
                 .ValueOrDie();
  } else {
    search = continuous::Percentile<int64_t>::Builder()
                 .SetPercentile(percentile)
                 .SetEpsilon(config->epsilon)
                 .SetMaxPartitionsContributed(l0_sensitivity)
                 .SetMaxContributionsPerPartition(linf_sensitivity)
                 .Build()
                 .ValueOrDie();
  }
  for (auto i : l) {
    search->AddEntry(i.cast<int64_t>());
  }

  return GetValue<int64_t>(search->PartialResult(privacy_budget).ValueOrDie());
}

// Common functions

BoundedFunctionHelperObject* NewBoundedFunctionObject(double epsilon, int lower_bound,
                                                      int upper_bound) {
  has_bounds = true;
  return new BoundedFunctionHelperObject{epsilon, lower_bound, upper_bound};
}

BoundedFunctionHelperObject* NewBoundedFunctionObject1(double epsilon) {
  has_bounds = false;
  return new BoundedFunctionHelperObject{epsilon};
}

void DeleteBoundedFunctionObject(BoundedFunctionHelperObject* config) {
  delete config;
};

void set_l0_sensitivity_(int _l0_sensitivity) {
  l0_sensitivity = _l0_sensitivity;
}

int get_l0_sensitivity_() {
  return l0_sensitivity;
}

void set_linf_sensitivity_(int _linf_sensitivity) {
  linf_sensitivity = _linf_sensitivity;
}

int get_linf_sensitivity_() {
  return linf_sensitivity;
}

}  // end namespace differential_privacy
}  // end extern "C"

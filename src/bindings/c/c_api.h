#ifndef DIFFERENTIAL_PRIVACY_C_C_API_H_
#define DIFFERENTIAL_PRIVACY_C_C_API_H_

#include <stddef.h>
#include <stdint.h>

#include "pybind11/pybind11.h"

#ifdef __cplusplus
extern "C" {
#endif

// Common Functions for all Bounded Functions

typedef struct BoundedFunctionHelperObject {
  double epsilon;
  int lower_bound;
  int upper_bound;
  int l0_sensitivity;
  int linf_sensitivity;
} BoundedFunctionHelperObject;

extern BoundedFunctionHelperObject* NewBoundedFunctionObject(double epsilon,
                                                             int lower_bound,
                                                             int upper_bound);

extern BoundedFunctionHelperObject* NewBoundedFunctionObject1(double epsilon);

extern void DeleteBoundedFunctionObject(BoundedFunctionHelperObject* config);

// Bounded Mean
extern double Result_BoundedMean(BoundedFunctionHelperObject* config, pybind11::list a);

extern double Result_BoundedSum(BoundedFunctionHelperObject* config, pybind11::list a);

extern double Result_BoundedStandardDeviation(BoundedFunctionHelperObject* config,
                                              pybind11::list a);

extern double Result_BoundedVariance(BoundedFunctionHelperObject* config,
                                     pybind11::list a);

// Order statistics
extern int64_t Result_Max(BoundedFunctionHelperObject* config, pybind11::list a,
                          double privacy_budget);

extern int64_t Result_Min(BoundedFunctionHelperObject* config, pybind11::list a,
                          double privacy_budget);

extern int64_t Result_Median(BoundedFunctionHelperObject* config, pybind11::list a,
                             double privacy_budget);

extern int64_t Result_Percentile(BoundedFunctionHelperObject* config, pybind11::list a,
                                 double privacy_budget, double percentile);

extern void set_l0_sensitivity_(int _l0_sensitivity);

extern int get_l0_sensitivity_();

extern void set_linf_sensitivity_(int _linf_sensitivity);

extern int get_linf_sensitivity_();

#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif  // DIFFERENTIAL_PRIVACY_C_C_API_H_

#ifndef DIFFERENTIAL_PRIVACY_C_C_API_H_
#define DIFFERENTIAL_PRIVACY_C_C_API_H_

#include <stddef.h>
#include <stdint.h>

#include "pybind11/pybind11.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DP_BoundedMeanInt {
  double epsilon;
  int lower;
  int upper;

} DP_BoundedMeanInt;

extern DP_BoundedMeanInt* DP_NewBoundedMean(double epsilon, int lower, int upper);

extern DP_BoundedMeanInt* DP_NewBoundedMean1(double epsilon);

extern void DP_DeleteBoundedMean(DP_BoundedMeanInt* config);

extern double DP_ResultBoundedMean(DP_BoundedMeanInt* config, pybind11::list a);

#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif  // DIFFERENTIAL_PRIVACY_C_C_API_H_

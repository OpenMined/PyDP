#ifndef DIFFERENTIAL_PRIVACY_C_C_API_H_
#define DIFFERENTIAL_PRIVACY_C_C_API_H_

#include <stddef.h>
#include <stdint.h>

#include "tensorflow/c/tf_attrtype.h"
#include "tensorflow/c/tf_datatype.h"
#include "tensorflow/c/tf_status.h"
#include "tensorflow/c/tf_tensor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DP_BoundedMeanInt {
  double epsilon;
  int lower;
  int upper;

} DP_BoundedMeanInt;

extern DP_BoundedMeanInt* DP_NewBoundedMeanInt_Build(double* epsilon,
                                                     int* lower, int* upper);

extern double DP_NewBoundedMeanIntResult(DP_BoundedMeanInt* config, int begin,
                                         int end);

#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif  // DIFFERENTIAL_PRIVACY_C_C_API_H_

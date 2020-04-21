#ifndef DIFFERENTIAL_PRIVACY_C_C_API_H_
#define DIFFERENTIAL_PRIVACY_C_C_API_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DP_BoundedMeanInt {
  double epsilon;
  int lower;
  int upper;

} DP_BoundedMeanInt;

extern DP_BoundedMeanInt* DP_BoundedMeanInt_New(double epsilon, int lower, int upper);

extern void DP_BoundedMeanInt_Delete(DP_BoundedMeanInt* config);

extern double DP_BoundedMeanInt_Result(DP_BoundedMeanInt* config, int begin, int end);


#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif  // DIFFERENTIAL_PRIVACY_C_C_API_H_

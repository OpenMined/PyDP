// Provides bindings for Bounded Functions

#include "pybind11/complex.h"
#include "pybind11/functional.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include "algorithms/algorithm.h"
#include "algorithms/bounded-mean.h"
#include "algorithms/bounded-standard-deviation.h"
#include "algorithms/bounded-sum.h"
#include "algorithms/bounded-variance.h"

#include "../pydp_lib/algorithm_builder.hpp"

namespace py = pybind11;
namespace dp = differential_privacy;

template <typename T, class Algorithm>
void declareBoundedAlgorithm(py::module& m) {
  using builder = typename dp::python::AlgorithmBuilder<T, Algorithm>;
  builder().declare(m);
}

void init_algorithms_bounded_functions(py::module& m) {
  declareBoundedAlgorithm<int, dp::BoundedMean<int>>(m);
  declareBoundedAlgorithm<int64_t, dp::BoundedMean<int64_t>>(m);
  declareBoundedAlgorithm<double, dp::BoundedMean<double>>(m);

  declareBoundedAlgorithm<int, dp::BoundedSum<int>>(m);
  declareBoundedAlgorithm<int64_t, dp::BoundedSum<int64_t>>(m);
  declareBoundedAlgorithm<double, dp::BoundedSum<double>>(m);

  declareBoundedAlgorithm<int, dp::BoundedStandardDeviation<int>>(m);
  declareBoundedAlgorithm<int64_t, dp::BoundedStandardDeviation<int64_t>>(m);
  declareBoundedAlgorithm<double, dp::BoundedStandardDeviation<double>>(m);

  declareBoundedAlgorithm<int, dp::BoundedVariance<int>>(m);
  declareBoundedAlgorithm<int64_t, dp::BoundedVariance<int64_t>>(m);
  declareBoundedAlgorithm<double, dp::BoundedVariance<double>>(m);
}

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
#include "../pydp_lib/casting.hpp"  // our caster helper library

using namespace std;

namespace py = pybind11;
namespace dp = differential_privacy;

template <typename T, class Algorithm>
void declareBoundedAlgorithm(py::module& m) {
  using builder = typename dp::python::AlgorithmBuilder<T, Algorithm>;
  builder().declare(m);
}

void init_algorithms_bounded_functions(py::module& m) {
  declareBoundedAlgorithm<int, dp::BoundedMean<int>>(m);
  declareBoundedAlgorithm<double, dp::BoundedMean<double>>(m);
  declareBoundedAlgorithm<long long, dp::BoundedMean<long long>>(m);

  declareBoundedAlgorithm<int, dp::BoundedSum<int>>(m);
  declareBoundedAlgorithm<double, dp::BoundedSum<double>>(m);
  declareBoundedAlgorithm<long long, dp::BoundedSum<long long>>(m);

  declareBoundedAlgorithm<int, dp::BoundedStandardDeviation<int>>(m);
  declareBoundedAlgorithm<double, dp::BoundedStandardDeviation<double>>(m);
  declareBoundedAlgorithm<long long, dp::BoundedStandardDeviation<long long>>(m);

  declareBoundedAlgorithm<int, dp::BoundedVariance<int>>(m);
  declareBoundedAlgorithm<double, dp::BoundedVariance<double>>(m);
  declareBoundedAlgorithm<long long, dp::BoundedVariance<long long>>(m);
}

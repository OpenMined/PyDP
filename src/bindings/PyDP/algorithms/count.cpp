// Provides bindings for algorithms count

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include "algorithms/count.h"

#include "../pydp_lib/algorithm_builder.hpp"

namespace py = pybind11;
namespace dp = differential_privacy;

template <typename T, class Algorithm>
void declareAlgorithm(py::module& m) {
  using builder = typename dp::python::AlgorithmBuilder<T, Algorithm>;
  builder().declare(m);
}

void init_algorithms_count(py::module& m) {
  declareAlgorithm<int, dp::Count<int>>(m);
  declareAlgorithm<int64_t, dp::Count<int64_t>>(m);
  declareAlgorithm<double, dp::Count<double>>(m);
}

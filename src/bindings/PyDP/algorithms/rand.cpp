// Provides bindings for rand
#include "differential_privacy/algorithms/rand.h"
#include "../pydp_lib/casting.hpp"
#include "pybind11/pybind11.h"

namespace py = pybind11;
namespace dp = differential_privacy;

void declareRandFunctions(py::module& m) {
  m.def("UniformDouble", &dp::UniformDouble);
  m.def("Geometric", &dp::Geometric);
}

void init_algorithms_rand(py::module& m) {
  declareRandFunctions(m);
}

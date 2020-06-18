// Provides bindings for Util

#include "pybind11/pybind11.h"

#include "algorithms/util.h"

namespace py = pybind11;
namespace dp = differential_privacy;

void init_algorithms_util(py::module& m) {
  py::module util = m.def_submodule("util", "Some Utility Functions");

  util.def("xor_strings", &dp::XorStrings);
  util.def("default_epsilon", &dp::DefaultEpsilon);
  util.def("get_next_power_of_two", &dp::GetNextPowerOfTwo);
  util.def("qnorm", &dp::Qnorm);
}

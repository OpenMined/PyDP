// Provides bindings for Util

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include "differential_privacy/algorithms/util.h"

namespace py = pybind11;
namespace dp = differential_privacy;

void init_algorithms_util(py::module& m) {
  py::module util = m.def_submodule("util", "Some Utility Functions");

  util.def("xor_strings", &dp::XorStrings);
  util.def("default_epsilon", &dp::DefaultEpsilon);
  util.def("get_next_power_of_two", &dp::GetNextPowerOfTwo);
  util.def("qnorm", &dp::Qnorm);
  util.def("mean", &dp::Mean<double>);
  util.def("mean", &dp::Mean<int>);
  util.def("variance", &dp::Variance<double>);
  util.def("standard_deviation", &dp::StandardDev<double>);
  util.def("order_statistics", &dp::OrderStatistic<double>);
  util.def("correlation", &dp::Correlation<double>);
  util.def("vector_filter", &dp::VectorFilter<double>);
  util.def("vector_to_string", &dp::VectorToString<double>);
}
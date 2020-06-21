// Provides bindings for Util

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include "algorithms/util.h"

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
  util.def("round_to_nearest_multiple", &dp::RoundToNearestMultiple);
  util.def("safe_add", [](int64_t i, int64_t j) {
    int64_t k;
    bool result = dp::SafeAdd(i, j, &k);
    if (result) return k;
    throw std::runtime_error("Result of addition will overflow.");
  });
  util.def("safe_subtract", [](int64_t i, int64_t j) {
    int64_t k;
    bool result = dp::SafeSubtract(i, j, &k);
    if (result) return k;
    throw std::runtime_error("Result of subtraction will overflow.");
  });
  util.def("safe_square", [](int64_t i) {
    int64_t k;
    bool result = dp::SafeSquare(i, &k);
    if (result) return k;
    throw std::runtime_error("Result of squaring will overflow.");
  });
}
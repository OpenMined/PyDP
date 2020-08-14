// Provides bindings for Util

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include "algorithms/util.h"

namespace py = pybind11;
namespace dp = differential_privacy;

void init_algorithms_util(py::module& m) {
  m.attr("__module__") = "pydp";
  m.def("xor_strings", &dp::XorStrings);
  m.def("default_epsilon", &dp::DefaultEpsilon);
  m.def("get_next_power_of_two", &dp::GetNextPowerOfTwo);
  m.def("qnorm", &dp::Qnorm);
  m.def("mean", &dp::Mean<double>);
  m.def("mean", &dp::Mean<int>);
  m.def("variance", &dp::Variance<double>);
  m.def("standard_deviation", &dp::StandardDev<double>);
  m.def("order_statistics", &dp::OrderStatistic<double>);
  m.def("correlation", &dp::Correlation<double>);
  m.def("vector_filter", &dp::VectorFilter<double>);
  m.def("vector_to_string", &dp::VectorToString<double>);
  m.def("round_to_nearest_multiple", &dp::RoundToNearestMultiple);
  m.def("safe_add", [](int64_t i, int64_t j) {
    int64_t k;
    bool result = dp::SafeAdd(i, j, &k);
    if (result) return k;
    throw std::runtime_error("Result of addition will overflow.");
  });
  m.def("safe_subtract", [](int64_t i, int64_t j) {
    int64_t k;
    bool result = dp::SafeSubtract(i, j, &k);
    if (result) return k;
    throw std::runtime_error("Result of subtraction will overflow.");
  });
  m.def("safe_square", [](int64_t i) {
    int64_t k;
    bool result = dp::SafeSquare(i, &k);
    if (result) return k;
    throw std::runtime_error("Result of squaring will overflow.");
  });
}

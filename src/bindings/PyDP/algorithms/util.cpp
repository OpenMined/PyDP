// Provides bindings for Util

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include "algorithms/util.h"

namespace py = pybind11;
namespace dp = differential_privacy;

void init_algorithms_util(py::module& m) {
  m.attr("__module__") = "pydp";
  m.def("default_epsilon", &dp::DefaultEpsilon);  // deprecated, default epsilon value
  m.def(
      "get_next_power_of_two", &dp::GetNextPowerOfTwo,
      R"pbdoc(Outputs value of a power of two that is greater than and closest to the given numerical input.)pbdoc");
  m.def(
      "qnorm", &dp::Qnorm,
      R"pbdoc(Quantile function of normal distribution, inverse of the cumulative distribution function.)pbdoc");
  m.def(
      "mean", &dp::Mean<double>,
      R"pbdoc(Calculation of the mean of given set of numbers for a double int data type.)pbdoc");
  m.def(
      "mean", &dp::Mean<int>,
      R"pbdoc(Calculation of the mean of given set of numbers for an int data type.)pbdoc");
  m.def("variance", &dp::Variance<double>,
        R"pbdoc(Calculate variance for a set of values.)pbdoc");
  m.def("standard_deviation", &dp::StandardDev<double>,
        R"pbdoc(Standard Deviation, the square root of variance.)pbdoc");
  m.def("order_statistics", &dp::OrderStatistic<double>,
        R"pbdoc(Sample values placed in ascending order.)pbdoc");
  m.def("correlation", &dp::Correlation<double>,
        R"pbdoc(Returns linear correlation coefficient.)pbdoc");
  m.def(
      "vector_filter", &dp::VectorFilter<double>,
      R"pbdoc(Filtering a vector using a logical operatio with only values selected using true output in their positions.)pbdoc");
  m.def("vector_to_string", &dp::VectorToString<double>,
        R"pbdoc(Conversion of a vector to a string data type.)pbdoc");
}

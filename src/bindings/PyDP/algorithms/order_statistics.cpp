// Provides bindings for Order Statistics
#include "algorithms/order-statistics.h"
#include "pybind11/complex.h"
#include "pybind11/functional.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include "../pydp_lib/algorithm_builder.hpp"

namespace py = pybind11;
namespace dp = differential_privacy;

template <typename T, class OrderStat>
void declareOrderStat(py::module& m) {
  using builder = typename dp::python::AlgorithmBuilder<T, OrderStat>;
  builder().declare(m);
}

void init_algorithms_order_statistics(py::module& m) {
  declareOrderStat<int, dp::continuous::Max<int>>(m);
  declareOrderStat<int64_t, dp::continuous::Max<int64_t>>(m);
  declareOrderStat<double, dp::continuous::Max<double>>(m);

  declareOrderStat<int, dp::continuous::Min<int>>(m);
  declareOrderStat<int64_t, dp::continuous::Min<int64_t>>(m);
  declareOrderStat<double, dp::continuous::Min<double>>(m);

  declareOrderStat<int, dp::continuous::Median<int>>(m);
  declareOrderStat<int64_t, dp::continuous::Median<int64_t>>(m);
  declareOrderStat<double, dp::continuous::Median<double>>(m);

  declareOrderStat<int, dp::continuous::Percentile<int>>(m);
  declareOrderStat<int64_t, dp::continuous::Percentile<int64_t>>(m);
  declareOrderStat<double, dp::continuous::Percentile<double>>(m);
}

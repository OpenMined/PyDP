#include "pybind11/embed.h"

using namespace std;

namespace py = pybind11;

// base
void init_base_status(py::module &);
void init_base_logging(py::module &);
void init_base_percentile(py::module &);

// bounded functions
void init_algorithms_bounded_functions(py::module &);

// util
void init_algorithms_util(py::module &);

// distributions
void init_algorithms_distributions(py::module &);

// order statistics
void init_algorithms_order_statistics(py::module &);

// proto
void init_proto(py::module &);

PYBIND11_MODULE(pydp, m) {
  m.doc() = "Google Differential Privacy python extension";

  // Base
  init_base_status(m);
  init_base_logging(m);
  init_base_percentile(m);

  // Algorithms
  init_algorithms_bounded_functions(m);
  init_algorithms_util(m);
  init_algorithms_distributions(m);
  init_algorithms_order_statistics(m);

  // Proto
  init_proto(m);
}

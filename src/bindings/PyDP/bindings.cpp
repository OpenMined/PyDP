#include "pybind11/embed.h"

using namespace std;

namespace py = pybind11;

// base
void init_base_status(py::module &);
void init_base_logging(py::module &);
void init_base_percentile(py::module &);

// algorithms
void init_algorithms_algorithms(py::module &);

// util
void init_algorithms_util(py::module &);

// distributions
void init_algorithms_distributions(py::module &);

// proto
void init_proto(py::module &);

PYBIND11_MODULE(pydp, m) {
  m.doc() = "Google Differential Privacy python extension";

  // Base
  init_base_status(m);
  init_base_logging(m);
  init_base_percentile(m);

  // Algorithms
  init_algorithms_algorithms(m);
  init_algorithms_util(m);
  init_algorithms_distributions(m);

  // Proto
  init_proto(m);
}

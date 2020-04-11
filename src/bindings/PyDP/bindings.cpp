#include "pybind11/embed.h"

using namespace std;

namespace py = pybind11;

// base
void init_base_status(py::module &);
void init_base_logging(py::module &);

// algorithms
void init_algorithms(py::module &);

// proto
void init_proto(py::module &);

PYBIND11_MODULE(pydp, m) {
  m.doc() = "Google Differential Privacy python extension";

  init_base_status(m);
  init_base_logging(m);

  init_algorithms(m);

  init_proto(m);
}

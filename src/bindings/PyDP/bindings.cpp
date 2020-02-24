#include "pybind11/embed.h"


using namespace std;

namespace py = pybind11;

void init_base_status(py::module &);
void init_base_logging(py::module &);

PYBIND11_MODULE(pydp, m) {

    m.doc() = "Google Differential Privacy python extension";

    init_base_status(m);
    init_base_logging(m);

}


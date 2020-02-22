#include "pybind11/embed.h"


using namespace std;

namespace py = pybind11;

void init_base_statusor(py::module &);
void init_base_status(py::module &);
void init_base_canonical_errors(py::module &);

PYBIND11_MODULE(pydp, m) {

    m.doc() = "Google Differential Privacy python extension";

    init_base_status(m);
    init_base_statusor(m);
    init_base_canonical_errors(m);

}


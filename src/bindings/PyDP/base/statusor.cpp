#include <string>

#include "pybind11/embed.h"
#include "differential_privacy/base/status.h"
#include "differential_privacy/base/statusor.h"

namespace py = pybind11;

void init_base_statusor(py::module &m) {
    m.def("Crash", &differential_privacy::base::statusor_internal::Helper::Crash, "Crash helper function");
}



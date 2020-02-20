#include <string>

#include "differential_privacy/base/status.h"
#include "differential_privacy/base/statusor.h"

#include "../pydp_lib/casting.hpp" // our caster helper library

namespace py = pybind11;

void init_base_statusor(py::module &m) {
    m.def("Crash", &differential_privacy::base::statusor_internal::Helper::Crash, "Crash helper function");
}



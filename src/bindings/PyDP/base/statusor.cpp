#include <string>

#include "differential_privacy/base/status.h"
#include "differential_privacy/base/statusor.h"

#include "../pydp_lib/casting.hpp" // our caster helper library

namespace py = pybind11;
namespace dpbase = differential_privacy::base;

void init_base_statusor(py::module &m) {

    m.def("handle_invalid_status_ctor_arg", &dpbase::statusor_internal::Helper::HandleInvalidStatusCtorArg);
    m.def("crash", &dpbase::statusor_internal::Helper::Crash, "Crash helper function");

}



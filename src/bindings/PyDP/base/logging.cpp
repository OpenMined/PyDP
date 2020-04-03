// Provides bindings for base/canonical_errors

#include <string>

#include "pybind11/pybind11.h"

#include "differential_privacy/base/logging.h" // the header file associated with logging.cc
#include "../pydp_lib/casting.hpp" // our caster helper library

namespace py = pybind11;
namespace dpbase = differential_privacy::base;


void init_base_logging(py::module &m) {

    auto msub = m.def_submodule("logging");

    msub.def("get_log_directory", &dpbase::get_log_directory, "Get the current logging directory");
    msub.def("get_vlog_level", &dpbase::get_vlog_level, "Get the current logging verbosity level");
    msub.def("init_logging", &dpbase::InitLogging, "Begin logging");
}
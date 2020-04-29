// Provides bindings for base/canonical_errors

#include <iostream>
#include <string>

#include "pybind11/pybind11.h"

#include "../pydp_lib/casting.hpp"              // our caster helper library
#include "differential_privacy/base/logging.h"  // the header file associated with logging.cc

namespace py = pybind11;
namespace dpb = differential_privacy::base;

class Logging_helper {
 public:
  Logging_helper(const char* directory, const char* file_name, int level) {
    dpb::InitLogging(directory, file_name, level);
  }
  int get_vlog_level() {
    return dpb::get_vlog_level();
  }

  std::__cxx11::string get_log_directory() {
    return dpb::get_log_directory();
  }
};

void init_base_logging(py::module& m) {
  py::class_<Logging_helper> obje(m, "Logging");
  obje.def(py::init<const char*, const char*, int>());

  // cannot set these two properites it as set log_directory and v_log level is
  // in anonymous namespace
  // https://github.com/google/differential-privacy/blob/master/differential_privacy/base/logging.cc#L42
  obje.def_property_readonly("log_directory", &Logging_helper::get_log_directory);
  obje.def_property_readonly("vlog_level", &Logging_helper::get_vlog_level);
}

#ifndef PYDP_LIB_STATUS_ERRORS_H_
#define PYDP_LIB_STATUS_ERRORS_H_

#include <pybind11/pybind11.h>

#include <string>

#include "absl/status/status.h"

namespace py = pybind11;

namespace differential_privacy {
namespace python {

// Raises a Python exception for a non-OK absl::Status coming back from the DP
// library, picking the exception type based on the status code instead of
// collapsing every failure into a generic RuntimeError.
//
// This lets callers distinguish, for example, a bad argument they passed in
// (ValueError) from a method that simply isn't implemented for a given
// algorithm (NotImplementedError), the same way they would for any other
// Python API. Status codes that don't have an obviously better fit (Internal,
// FailedPrecondition, etc.) keep raising RuntimeError, which was already the
// behavior for every code before this.
//
// `status` is expected to be non-OK; callers should check status.ok() (or
// statusor.ok()) first.
inline void ThrowFromStatus(const absl::Status& status) {
  const std::string message = status.ToString();
  switch (status.code()) {
    case absl::StatusCode::kInvalidArgument:
      throw py::value_error(message);
    case absl::StatusCode::kUnimplemented:
      PyErr_SetString(PyExc_NotImplementedError, message.c_str());
      throw py::error_already_set();
    default:
      throw std::runtime_error(message);
  }
}

}  // namespace python
}  // namespace differential_privacy

#endif  // PYDP_LIB_STATUS_ERRORS_H_

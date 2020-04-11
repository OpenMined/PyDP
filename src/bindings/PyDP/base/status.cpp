// Provides bindings for base/status and related

#include <string>

#include "../pydp_lib/casting.hpp"  // our caster helper library
#include "pybind11/operators.h"     // for overloading the operators
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include "differential_privacy/base/canonical_errors.h"  // the header file associated with status.cc
#include "differential_privacy/base/status.h"  // the header file associated with status.cc
#include "differential_privacy/base/statusor.h"  //header file associated with statusor.cc
#include "differential_privacy/proto/data.pb.h"  // for Output type

using namespace std;

namespace py = pybind11;
using namespace py::literals;
namespace dp = differential_privacy;
// namespace dpbase = differential_privacy::base;

template <typename T>
void declareStatusOr(py::module &m, string const &suffix) {
  py::class_<dp::base::StatusOr<T>> cls(m, ("StatusOr" + suffix).c_str());
  cls.def(py::init<>());
  cls.def(py::init<T>(), "value"_a);
  cls.def(py::init<dp::base::Status>(), "status"_a);
  cls.def("ok", &dp::base::StatusOr<T>::ok);
  // cls.def("value_or_die", &dp::base::StatusOr<T>::ValueOrDie<T>);
  // cls.def(py::self == dpbase::Status());
}

template <class Algorithm>
void declareStatusOr2(py::module &m, string const &suffix) {
  py::class_<dp::base::StatusOr<Algorithm>> cls(m,
                                                ("StatusOr" + suffix).c_str());
  cls.def(py::init<>());
  // cls.def(py::init<Algorithm>(), "value"_a);
  cls.def(py::init<dp::base::Status>(), "status"_a);
  cls.def("ok", &dp::base::StatusOr<Algorithm>::ok);
  // cls.def("value_or_die", &dp::base::StatusOr<T>::ValueOrDie<T>);
  // cls.def(py::self == dpbase::Status());
}

void init_base_status(py::module &m) {
  // Creating the Status class
  py::class_<dp::base::Status> status(m, "Status");

  // Status class (we can now build functions and enuums from this class)
  status.def(py::init<dp::base::StatusCode &, std::string &>())
      .def("__repr__", &dp::base::Status::ToString,
           "String representation of status")
      .def("set_payload", &dp::base::Status::SetPayload,
           "Sets the status payload")
      .def("get_payload", &dp::base::Status::GetPayload,
           "Returns the status payload")
      .def("erase_payload", &dp::base::Status::ErasePayload,
           "Erases at target url");

  // scoped enumerator for Status Code
  py::enum_<dp::base::StatusCode>(status, "StatusCode", py::arithmetic())
      .value("kOk", dp::base::StatusCode::kOk)
      .value("kCancelled", dp::base::StatusCode::kCancelled)
      .value("kUnknown", dp::base::StatusCode::kUnknown)
      .value("kInvalidArgument", dp::base::StatusCode::kInvalidArgument)
      .value("kDeadlineExceeded", dp::base::StatusCode::kDeadlineExceeded)
      .value("kNotFound", dp::base::StatusCode::kNotFound)
      .value("kAlreadyExists", dp::base::StatusCode::kAlreadyExists)
      .value("kPermissionDenied", dp::base::StatusCode::kPermissionDenied)
      .value("kResourceExhausted", dp::base::StatusCode::kResourceExhausted)
      .value("kFailedPrecondition", dp::base::StatusCode::kFailedPrecondition)
      .value("kAborted", dp::base::StatusCode::kAborted)
      .value("kOutOfRange", dp::base::StatusCode::kOutOfRange)
      .value("kUnimplemented", dp::base::StatusCode::kUnimplemented)
      .value("kInternal", dp::base::StatusCode::kInternal)
      .value("kUnavailable", dp::base::StatusCode::kUnavailable)
      .value("kDataLoss", dp::base::StatusCode::kDataLoss)
      .value("kUnauthenticated", dp::base::StatusCode::kUnauthenticated)
      .value("kDoNotUseReservedForFutureExpansionUseDefaultInSwitchInstead_",
             dp::base::StatusCode::
                 kDoNotUseReservedForFutureExpansionUseDefaultInSwitchInstead_);

  // converts a status code  to a nice string
  status.def("status_code_to_string", &dp::base::StatusCodeToString,
             "converts status code to string");

  // canonical errors
  status.def("aborted_error", &dp::base::AbortedError);
  status.def("aborted_error", &dp::base::AbortedError);
  status.def("already_exists_error", &dp::base::AlreadyExistsError);
  status.def("cancelled_error", &dp::base::CancelledError);
  status.def("data_loss_error", &dp::base::DataLossError);
  status.def("deadline_exceeded_error", &dp::base::DeadlineExceededError);
  status.def("failed_precondition_error", &dp::base::FailedPreconditionError);
  status.def("internal_error", &dp::base::InternalError);
  status.def("invalid_argument_error", &dp::base::InvalidArgumentError);
  status.def("not_found_error", &dp::base::NotFoundError);
  status.def("out_of_range_error", &dp::base::OutOfRangeError);
  status.def("permission_denied_error", &dp::base::PermissionDeniedError);
  status.def("resource_exhausted_error", &dp::base::ResourceExhaustedError);
  status.def("unauthenticated_error", &dp::base::UnauthenticatedError);
  status.def("unavailable_error", &dp::base::UnavailableError);
  status.def("unimplemented_error", &dp::base::UnimplementedError);
  status.def("unknown_error", &dp::base::UnknownError);

  // from statusor
  m.def("handle_invalid_status_ctor_arg",
        &dp::base::statusor_internal::Helper::HandleInvalidStatusCtorArg);
  m.def("crash", &dp::base::statusor_internal::Helper::Crash,
        "Crash helper function");

  declareStatusOr<double>(m, "D");
  declareStatusOr<dp::Output>(m, "O");

  // declareStatusOr2 is only a little different from declareStatusOr
  // (see above in this file).
  // Using declareStatusOr (without "2" at the end) below results in this error:
  // external/google_dp/differential_privacy/base/statusor_internals.h:104:60:
  // error: use of deleted function
  // 'differential_privacy::BoundedMean<int>::BoundedMean(differential_privacy::BoundedMean<int>&&)'
  declareStatusOr2<typename dp::BoundedMean<int>>(m, "BoundedMeantInt");
}

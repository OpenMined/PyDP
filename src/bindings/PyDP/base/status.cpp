// Provides bindings for base/status and related

#include <string>

#include "../pydp_lib/casting.hpp"  // our caster helper library
#include "pybind11/operators.h"     // for overloading the operators
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include "base/canonical_errors.h"  // the header file associated with status.cc
#include "base/status.h"            // the header file associated with status.cc
#include "base/statusor.h"          //header file associated with statusor.cc
// #include "differential_privacy/proto/data.pb.h"  // for Output type

using namespace std;

namespace py = pybind11;
using namespace py::literals;
namespace dp = differential_privacy;
namespace dpb = differential_privacy::base;

template <typename T>
void declareStatusOr(py::module &m, string const &suffix) {
  py::class_<dpb::StatusOr<T>> cls(m, ("StatusOr" + suffix).c_str());
  cls.def(py::init<>());
  cls.def(py::init<T>(), "value"_a);
  cls.def(py::init<dpb::Status>(), "status"_a);
  cls.def("ok", &dpb::StatusOr<T>::ok);
  // cls.def("value_or_die", &dpb::StatusOr<T>::ValueOrDie<T>);
  // cls.def(py::self == dpbase::Status());
}

template <class Algorithm>
void declareStatusOr2(py::module &m, string const &suffix) {
  py::class_<dpb::StatusOr<Algorithm>> cls(m, ("StatusOr" + suffix).c_str());
  cls.def(py::init<>());
  // cls.def(py::init<Algorithm>(), "value"_a);
  cls.def(py::init<dpb::Status>(), "status"_a);
  cls.def("ok", &dpb::StatusOr<Algorithm>::ok);
  // cls.def("value_or_die", &dpb::StatusOr<T>::ValueOrDie<T>);
  // cls.def(py::self == dpbase::Status());
}

void init_base_status(py::module &m) {
  // Creating the Status class
  py::class_<dpb::Status> status(m, "Status");
  status.attr("__module__") = "pydp";
  // Status class (we can now build functions and enuums from this class)
  status.def(py::init<dpb::StatusCode &, std::string &>())
      .def("__repr__", &dpb::Status::ToString, "String representation of status")
      .def("set_payload", &dpb::Status::SetPayload, "Sets the status payload")
      .def("get_payload", &dpb::Status::GetPayload, "Returns the status payload")
      .def("erase_payload", &dpb::Status::ErasePayload, "Erases at target url");

  // scoped enumerator for Status Code
  py::enum_<dpb::StatusCode>(status, "StatusCode", py::arithmetic())
      .value("kOk", dpb::StatusCode::kOk)
      .value("kCancelled", dpb::StatusCode::kCancelled)
      .value("kUnknown", dpb::StatusCode::kUnknown)
      .value("kInvalidArgument", dpb::StatusCode::kInvalidArgument)
      .value("kDeadlineExceeded", dpb::StatusCode::kDeadlineExceeded)
      .value("kNotFound", dpb::StatusCode::kNotFound)
      .value("kAlreadyExists", dpb::StatusCode::kAlreadyExists)
      .value("kPermissionDenied", dpb::StatusCode::kPermissionDenied)
      .value("kResourceExhausted", dpb::StatusCode::kResourceExhausted)
      .value("kFailedPrecondition", dpb::StatusCode::kFailedPrecondition)
      .value("kAborted", dpb::StatusCode::kAborted)
      .value("kOutOfRange", dpb::StatusCode::kOutOfRange)
      .value("kUnimplemented", dpb::StatusCode::kUnimplemented)
      .value("kInternal", dpb::StatusCode::kInternal)
      .value("kUnavailable", dpb::StatusCode::kUnavailable)
      .value("kDataLoss", dpb::StatusCode::kDataLoss)
      .value("kUnauthenticated", dpb::StatusCode::kUnauthenticated)
      .value("kDoNotUseReservedForFutureExpansionUseDefaultInSwitchInstead_",
             dpb::StatusCode::
                 kDoNotUseReservedForFutureExpansionUseDefaultInSwitchInstead_);

  // converts a status code  to a nice string
  status.def("status_code_to_string", &dpb::StatusCodeToString,
             "converts status code to string");

  // canonical errors
  status.def("aborted_error", &dpb::AbortedError);
  status.def("aborted_error", &dpb::AbortedError);
  status.def("already_exists_error", &dpb::AlreadyExistsError);
  status.def("cancelled_error", &dpb::CancelledError);
  status.def("data_loss_error", &dpb::DataLossError);
  status.def("deadline_exceeded_error", &dpb::DeadlineExceededError);
  status.def("failed_precondition_error", &dpb::FailedPreconditionError);
  status.def("internal_error", &dpb::InternalError);
  status.def("invalid_argument_error", &dpb::InvalidArgumentError);
  status.def("not_found_error", &dpb::NotFoundError);
  status.def("out_of_range_error", &dpb::OutOfRangeError);
  status.def("permission_denied_error", &dpb::PermissionDeniedError);
  status.def("resource_exhausted_error", &dpb::ResourceExhaustedError);
  status.def("unauthenticated_error", &dpb::UnauthenticatedError);
  status.def("unavailable_error", &dpb::UnavailableError);
  status.def("unimplemented_error", &dpb::UnimplementedError);
  status.def("unknown_error", &dpb::UnknownError);

  // from statusor
  m.def("handle_invalid_status_ctor_arg",
        &dpb::statusor_internal::Helper::HandleInvalidStatusCtorArg);
  m.def("crash", &dpb::statusor_internal::Helper::Crash, "Crash helper function");

  declareStatusOr<double>(m, "D");
  // declareStatusOr<dp::Output>(m, "O");

  // declareStatusOr2 is only a little different from declareStatusOr
  // (see above in this file).
  // Using declareStatusOr (without "2" at the end) below results in this error:
  // external/google_dp/differential_privacy/base/statusor_internals.h:104:60:
  // error: use of deleted function
  // 'differential_privacy::BoundedMean<int>::BoundedMean(differential_privacy::BoundedMean<int>&&)'
  // declareStatusOr2<typename dp::BoundedMean<int>>(m, "BoundedMeantInt");
}

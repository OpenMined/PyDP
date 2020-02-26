// Provides bindings for base/status and related

#include <string>

#include "pybind11/pybind11.h"
#include "../pydp_lib/casting.hpp" // our caster helper library
#include "pybind11/operators.h" // for overloading the operators

#include "differential_privacy/base/status.h" // the header file associated with status.cc
#include "differential_privacy/base/canonical_errors.h" // the header file associated with status.cc
#include "differential_privacy/base/statusor.h" //header file associated with statusor.cc

using namespace std;

namespace py = pybind11;
using namespace py::literals;
namespace dpbase = differential_privacy::base;


template<typename T>
void declareStatusOr(py::module & m, string const & suffix) {
    py::class_<dpbase::StatusOr<T>> cls(m, ("StatusOr" + suffix).c_str());
    cls.def(py::init<>());
    cls.def(py::init<T>(), "value"_a);
    cls.def(py::init<dpbase::Status>(), "status"_a);
    cls.def("ok", &dpbase::StatusOr<T>::ok);
    //cls.def(py::self == dpbase::Status());

}

void init_base_status(py::module &m) {

    // Creating the Status class
    py::class_<dpbase::Status> status(m, "Status");

    // Status class (we can now build functions and enuums from this class)
    status.def(py::init<dpbase::StatusCode &, std::string &>())
        .def("__repr__", &dpbase::Status::ToString, "String representation of status")
        .def("set_payload", &dpbase::Status::SetPayload, "Sets the status payload")
        .def("get_payload", &dpbase::Status::GetPayload, "Returns the status payload")
        .def("erase_payload", &dpbase::Status::ErasePayload, "Erases at target url");
    

    // scoped enumerator for Status Code
    py::enum_<differential_privacy::base::StatusCode>(status,"StatusCode",py::arithmetic())
        .value("kOk", differential_privacy::base::StatusCode::kOk)
        .value("kCancelled", differential_privacy::base::StatusCode::kCancelled)
        .value("kUnknown", differential_privacy::base::StatusCode::kUnknown)
        .value("kInvalidArgument", differential_privacy::base::StatusCode::kInvalidArgument)
        .value("kDeadlineExceeded", differential_privacy::base::StatusCode::kDeadlineExceeded)
        .value("kNotFound", differential_privacy::base::StatusCode::kNotFound)
        .value("kAlreadyExists", differential_privacy::base::StatusCode::kAlreadyExists)
        .value("kPermissionDenied", differential_privacy::base::StatusCode::kPermissionDenied)
        .value("kResourceExhausted", differential_privacy::base::StatusCode::kResourceExhausted)
        .value("kFailedPrecondition", differential_privacy::base::StatusCode::kFailedPrecondition)
        .value("kAborted", differential_privacy::base::StatusCode::kAborted)
        .value("kOutOfRange", differential_privacy::base::StatusCode::kOutOfRange)
        .value("kUnimplemented", differential_privacy::base::StatusCode::kUnimplemented)
        .value("kInternal", differential_privacy::base::StatusCode::kInternal)
        .value("kUnavailable", differential_privacy::base::StatusCode::kUnavailable)
        .value("kDataLoss", differential_privacy::base::StatusCode::kDataLoss)
        .value("kUnauthenticated", differential_privacy::base::StatusCode::kUnauthenticated)
        .value("kDoNotUseReservedForFutureExpansionUseDefaultInSwitchInstead_", differential_privacy::base::StatusCode::kDoNotUseReservedForFutureExpansionUseDefaultInSwitchInstead_);


    //converts a status code  to a nice string
    m.def("status_code_to_string", &dpbase::StatusCodeToString, "converts status code to string");


    // canonical errors
    status.def("aborted_error", &dpbase::AbortedError);
    status.def("aborted_error", &dpbase::AbortedError);
    status.def("already_exists_error", &dpbase::AlreadyExistsError);
    status.def("cancelled_error", &dpbase::CancelledError);
    status.def("data_loss_error", &dpbase::DataLossError);
    status.def("deadline_exceeded_error", &dpbase::DeadlineExceededError);
    status.def("failed_precondition_error", &dpbase::FailedPreconditionError);
    status.def("internal_error", &dpbase::InternalError);
    status.def("invalid_argument_error", &dpbase::InvalidArgumentError);
    status.def("not_found_error", &dpbase::NotFoundError);
    status.def("out_of_range_error", &dpbase::OutOfRangeError);
    status.def("permission_denied_error", &dpbase::PermissionDeniedError);
    status.def("resource_exhausted_error", &dpbase::ResourceExhaustedError);
    status.def("unauthenticated_error", &dpbase::UnauthenticatedError);
    status.def("unavailable_error", &dpbase::UnavailableError);
    status.def("unimplemented_error", &dpbase::UnimplementedError);
    status.def("unknown_error", &dpbase::UnknownError);

    // from statusor
    m.def("handle_invalid_status_ctor_arg", &dpbase::statusor_internal::Helper::HandleInvalidStatusCtorArg);
    m.def("crash", &dpbase::statusor_internal::Helper::Crash, "Crash helper function");

    declareStatusOr<double>(m, "D");

}



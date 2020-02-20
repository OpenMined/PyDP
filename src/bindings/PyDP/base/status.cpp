// Provides bindings for base/status


#include <string>

#include "pybind11/pybind11.h"

#include "differential_privacy/base/status.h" // the header file associated with status.cc
#include "../pydp_lib/casting.hpp" // our caster helper library

namespace py = pybind11;
namespace dpbase = differential_privacy::base;


void init_base_status(py::module &m) {


    py::class_<dpbase::Status>(m, "Status")
        .def(py::init<dpbase::StatusCode &, std::string &>())
        .def("__repr__", &dpbase::Status::ToString, "String representation of status")
        .def("set_payload", &dpbase::Status::SetPayload, "Sets the status payload")
        .def("get_payload", &dpbase::Status::GetPayload, "Returns the status payload")
        .def("erase_payload", &dpbase::Status::ErasePayload, "Erases at target url");
    

    py::enum_<differential_privacy::base::StatusCode>(m,"StatusCode",py::arithmetic())
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


    m.def("status_code_to_string", &dpbase::StatusCodeToString, "converts status code to string");

}



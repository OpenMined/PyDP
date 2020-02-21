// Provides bindings for base/canonical_errors


#include <string>

#include "pybind11/pybind11.h"

#include "differential_privacy/base/canonical_errors.h" // the header file associated with status.cc
#include "../pydp_lib/casting.hpp" // our caster helper library

namespace py = pybind11;
namespace dpbase = differential_privacy::base;


void init_base_canonical_errors(py::module &m) {

    auto msub = m.def_submodule("canonical_errors");

    msub.def("aborted_error", &dpbase::AbortedError);
    msub.def("already_exists_error", &dpbase::AlreadyExistsError);
    msub.def("cancelled_error", &dpbase::CancelledError);
    msub.def("data_loss_error", &dpbase::DataLossError);
    msub.def("deadline_exceeded_error", &dpbase::DeadlineExceededError);
    msub.def("failed_precondition_error", &dpbase::FailedPreconditionError);
    msub.def("internal_error", &dpbase::InternalError);
    msub.def("invalid_argument_error", &dpbase::InvalidArgumentError);
    msub.def("not_found_error", &dpbase::NotFoundError);
    msub.def("out_of_range_error", &dpbase::OutOfRangeError);
    msub.def("permission_denied_error", &dpbase::PermissionDeniedError);
    msub.def("resource_exhausted_error", &dpbase::ResourceExhaustedError);
    msub.def("unauthenticated_error", &dpbase::UnauthenticatedError);
    msub.def("unavailable_error", &dpbase::UnavailableError);
    msub.def("unimplemented_error", &dpbase::UnimplementedError);
    msub.def("unknown_error", &dpbase::UnknownError);


}
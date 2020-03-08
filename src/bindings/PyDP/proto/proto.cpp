#include <string>

#include "pybind11/pybind11.h"
#include "../pydp_lib/casting.hpp" // our caster helper library

#include "differential_privacy/proto/util.h" // the header file associated with status.cc
#include "differential_privacy/proto/data.pb.h"

using namespace std;

namespace py = pybind11;
using namespace py::literals;

namespace dp = differential_privacy;

void init_proto(py::module &m) {
    
    py::class_<dp::Output> output(m, "Output");

    output.def(py::init());


}
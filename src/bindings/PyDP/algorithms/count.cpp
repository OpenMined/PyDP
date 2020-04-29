// Provides bindings for algorithms

#include <string>

#include "../../c/c_api.h"
#include "../pydp_lib/casting.hpp"  // our caster helper library
#include "pybind11/complex.h"
#include "pybind11/functional.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"


#include "differential_privacy/algorithms/count.h"

using namespace std;

namespace py = pybind11;
namespace dp = differential_privacy;


// todo: make these generators work. refer to the statusor implementation for
// inspiration
// template<typename T>
// void declareCount(py::module & m, string const & suffix) {
//     py::class_<dp::Count<T>> cls(m, ("Count" + suffix).c_str());
//     cls.def(py::init<double, std::unique_ptr<dp::LaplaceMechanism>>(),
//     "epsilon"_a, "mechanism"_a);
// }

// template<typename T>
// void declareCountBuilder(py::module & m, string const & suffix) {
//     py::class_<dp::Count<T>::Builder> cls(m, ("Builder" + suffix).c_str());
//     //cls.def("Build", &dp::Count<T>::Builder::Build);
// }

void init_algorithms_count(py::module& m) {

}

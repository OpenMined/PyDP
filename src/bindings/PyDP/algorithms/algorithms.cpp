// Provides bindings for base/status and related

#include <string>

#include "pybind11/pybind11.h"
#include "../pydp_lib/casting.hpp" // our caster helper library

#include "differential_privacy/algorithms/algorithm.h"
#include "differential_privacy/algorithms/count.h"
#include "differential_privacy/algorithms/numerical-mechanisms.h"

using namespace std;

namespace py = pybind11;
using namespace py::literals;

namespace dp = differential_privacy;

 // helper class for Algorithm, which is a templated class
    template<typename T>
    void declareAlgorithm(py::module & m, string const & suffix) {
        py::class_<dp::Algorithm<T>> cls(m, ("Algorithm" + suffix).c_str());
        cls.def(py::init<double>(), "epsilon"_a);
    }

    // template<typename T>
    // void declareCount(py::module & m, string const & suffix) {
    //     py::class_<dp::Count<T>> cls(m, ("Count" + suffix).c_str());
    //     cls.def(py::init<double, std::unique_ptr<dp::LaplaceMechanism>>(), "epsilon"_a, "mechanism"_a);
    // }

    // template<typename T>
    // void declareCountBuilder(py::module & m, string const & suffix) {
    //     py::class_<dp::Count<T>::Builder> cls(m, ("Builder" + suffix).c_str());
    //     //cls.def("Build", &dp::Count<T>::Builder::Build);
    // }

void init_algorithms(py::module &m) {
    
    // declareCount<double, std::unique_ptr<dp::LaplaceMechanism>>(m, "D");

//    declareCountBuilder<double>(m, "D");

}
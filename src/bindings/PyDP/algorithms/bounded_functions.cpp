// Provides bindings for algorithms

#include <string>

#include "../../c/c_api.h"
#include "../pydp_lib/casting.hpp"  // our caster helper library
#include "pybind11/complex.h"
#include "pybind11/functional.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include "differential_privacy/algorithms/bounded-mean.h"
#include "differential_privacy/algorithms/bounded-sum.h"
#include "differential_privacy/algorithms/count.h"
#include "differential_privacy/algorithms/numerical-mechanisms.h"

PYBIND11_MAKE_OPAQUE(BoundedFunctionHelperObject);

using namespace std;

namespace py = pybind11;
namespace dp = differential_privacy;


class BoundedMeanDummy {
 public:
  BoundedMeanDummy(double epsilon, int lower, int upper) {
    obj = NewBoundedFunctionObject(epsilon, lower, upper);
  }

  BoundedMeanDummy(double epsilon) {
    obj = NewBoundedFunctionObject1(epsilon);
  }

  double Result(py::list l) {
    return Result_BoundedMean(obj, l);
  }

  ~BoundedMeanDummy() {
    DeleteBoundedFunctionObject(obj);
  }

  BoundedFunctionHelperObject* obj;
};

void declareBoundedMean(py::module& m) {
  py::class_<BoundedMeanDummy> bld(m, "BoundedMean");

  bld.def(py::init<double, int, int>(), py::return_value_policy::reference,
          py::call_guard<pybind11::gil_scoped_release>());
  bld.def(py::init<double>(), py::return_value_policy::reference,
          py::call_guard<pybind11::gil_scoped_release>());
  bld.def("result", &BoundedMeanDummy::Result);
}

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

void init_algorithms_bounded_functions(py::module& m) {
  declareBoundedMean(m);
}

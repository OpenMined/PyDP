// Provides bindings for Bounded Functions

#include "../../c/c_api.h"
#include "../pydp_lib/casting.hpp"  // our caster helper library
#include "pybind11/complex.h"
#include "pybind11/functional.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"


PYBIND11_MAKE_OPAQUE(BoundedFunctionHelperObject);

using namespace std;

namespace py = pybind11;


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

void init_algorithms_bounded_functions(py::module& m) {
  declareBoundedMean(m);
}

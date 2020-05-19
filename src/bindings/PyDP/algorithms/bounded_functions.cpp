// Provides bindings for Bounded Functions

#include "../../c/c_api.h"

#include "../pydp_lib/casting.hpp"       // our caster helper library
#include "../pydp_lib/helper_class.hpp"  //  Dummy helper class

#include "pybind11/complex.h"
#include "pybind11/functional.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

using namespace std;

namespace py = pybind11;

class BoundedMeanDummy : public Dummy {
 public:
  using Dummy::Dummy;
  double Result(py::list l) override {
    return Result_BoundedMean(obj, l);
  }
};

class BoundedSumDummy : public Dummy {
public:
  using Dummy::Dummy;
  double Result(py::list l) override {
    return Result_BoundedSum(obj, l);
  }
};

class BoundedStandardDeviationDummy : public Dummy {
public:
  using Dummy::Dummy;
  double Result(py::list l) override {
    return Result_BoundedStandardDeviation(obj, l);
  }
};

void declareBoundedMean(py::module& m) {
  py::class_<BoundedMeanDummy> bld(m, "BoundedMean");

  bld.def(py::init<double, int, int>(), py::return_value_policy::reference,
          py::call_guard<pybind11::gil_scoped_release>());
  bld.def(py::init<double>(), py::return_value_policy::reference,
          py::call_guard<pybind11::gil_scoped_release>());
  bld.def("result", &BoundedMeanDummy::Result);
}

void declareBoundedSum(py::module& m) {
  py::class_<BoundedSumDummy> cls(m, "BoundedSum");

  cls.def(py::init<double, int, int>(), py::return_value_policy::reference,
          py::call_guard<pybind11::gil_scoped_release>());
  cls.def(py::init<double>(), py::return_value_policy::reference,
          py::call_guard<pybind11::gil_scoped_release>());
  cls.def("result", &BoundedSumDummy::Result);
}

void declareBoundedStandardDeviation(py::module& m) {
  py::class_<BoundedStandardDeviationDummy> cls(m, "BoundedStandardDeviation");

  cls.def(py::init<double, int, int>(), py::return_value_policy::reference,
          py::call_guard<pybind11::gil_scoped_release>());
  cls.def(py::init<double>(), py::return_value_policy::reference,
          py::call_guard<pybind11::gil_scoped_release>());
  cls.def("result", &BoundedStandardDeviationDummy::Result);
}

void init_algorithms_bounded_functions(py::module& m) {
  declareBoundedMean(m);
  declareBoundedSum(m);
  declareBoundedStandardDeviation(m);
}

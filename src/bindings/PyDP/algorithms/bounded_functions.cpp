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

class BoundedVarianceDummy : public Dummy {
 public:
  using Dummy::Dummy;
  double Result(py::list l) override {
    return Result_BoundedVariance(obj, l);
  }
};

void declareBoundedMean(py::module& m) {
  py::class_<BoundedMeanDummy> bld(m, "BoundedMean");
  bld.attr("__module__") = "pydp";
  bld.def(py::init<double, int, int>(), py::return_value_policy::reference,
          py::call_guard<pybind11::gil_scoped_release>());
  bld.def(py::init<double>(), py::return_value_policy::reference,
          py::call_guard<pybind11::gil_scoped_release>());
  bld.def("result", &BoundedMeanDummy::Result);
  bld.def_property("l0_sensitvity", &BoundedMeanDummy::get_l0_sensitivity,
                   &BoundedMeanDummy::set_l0_sensitivity);
  bld.def_property("linf_sensitvity", &BoundedMeanDummy::get_linf_sensitivity,
                   &BoundedMeanDummy::set_linf_sensitivity);
}

void declareBoundedSum(py::module& m) {
  py::class_<BoundedSumDummy> cls(m, "BoundedSum");
  cls.attr("__module__") = "pydp";
  cls.def(py::init<double, int, int>(), py::return_value_policy::reference,
          py::call_guard<pybind11::gil_scoped_release>());
  cls.def(py::init<double>(), py::return_value_policy::reference,
          py::call_guard<pybind11::gil_scoped_release>());
  cls.def("result", &BoundedSumDummy::Result);
  cls.def_property("l0_sensitvity", &BoundedSumDummy::get_l0_sensitivity,
                   &BoundedSumDummy::set_l0_sensitivity);
  cls.def_property("linf_sensitvity", &BoundedSumDummy::get_linf_sensitivity,
                   &BoundedSumDummy::set_linf_sensitivity);
}

void declareBoundedStandardDeviation(py::module& m) {
  py::class_<BoundedStandardDeviationDummy> cls(m, "BoundedStandardDeviation");
  cls.attr("__module__") = "pydp";
  cls.def(py::init<double, int, int>(), py::return_value_policy::reference,
          py::call_guard<pybind11::gil_scoped_release>());
  cls.def(py::init<double>(), py::return_value_policy::reference,
          py::call_guard<pybind11::gil_scoped_release>());
  cls.def("result", &BoundedStandardDeviationDummy::Result);
  cls.def_property("l0_sensitvity", &BoundedStandardDeviationDummy::get_l0_sensitivity,
                   &BoundedStandardDeviationDummy::set_l0_sensitivity);
  cls.def_property("linf_sensitvity", &BoundedStandardDeviationDummy::get_linf_sensitivity,
                   &BoundedSumDummy::set_linf_sensitivity);
}

void declareBoundedVariance(py::module& m) {
  py::class_<BoundedVarianceDummy> cls(m, "BoundedVariance");
  cls.attr("__module__") = "pydp";
  cls.def(py::init<double, int, int>(), py::return_value_policy::reference,
          py::call_guard<pybind11::gil_scoped_release>());
  cls.def(py::init<double>(), py::return_value_policy::reference,
          py::call_guard<pybind11::gil_scoped_release>());
  cls.def("result", &BoundedVarianceDummy::Result);
  cls.def_property("l0_sensitvity", &BoundedVarianceDummy::get_l0_sensitivity,
                   &BoundedVarianceDummy::set_l0_sensitivity);
  cls.def_property("linf_sensitvity", &BoundedVarianceDummy::get_linf_sensitivity,
                   &BoundedVarianceDummy::set_linf_sensitivity);
}

void init_algorithms_bounded_functions(py::module& m) {
  declareBoundedMean(m);
  declareBoundedSum(m);
  declareBoundedStandardDeviation(m);
  declareBoundedVariance(m);
}

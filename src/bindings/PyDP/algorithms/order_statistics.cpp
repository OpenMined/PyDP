// Provides bindings for Bounded Functions

#include "../../c/c_api.h"

#include "../pydp_lib/casting.hpp"       // our caster helper library
#include "../pydp_lib/helper_class.hpp"  //  Dummy helder class

#include "pybind11/complex.h"
#include "pybind11/functional.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

using namespace std;

namespace py = pybind11;

class MaxDummy : public Dummy {
 public:
  using Dummy::Dummy;

  double Result(py::list l, double privacy_budget) override {
    return Result_Max(obj, l, privacy_budget);
  }
};

class MinDummy : public Dummy {
 public:
  using Dummy::Dummy;

  double Result(py::list l, double privacy_budget) override {
    return Result_Min(obj, l, privacy_budget);
  }
};

class MedianDummy : public Dummy {
 public:
  using Dummy::Dummy;

  double Result(py::list l, double privacy_budget) override {
    return Result_Median(obj, l, privacy_budget);
  }
};

class PercentileDummy : public Dummy {
 public:
  using Dummy::Dummy;

  void setPercentile(double percentile) {
    _percentile = percentile;
  }

  double getPercentile() {
    return _percentile;
  }

  double Result(py::list l, double privacy_budget) override {
    return Result_Percentile(obj, l, privacy_budget, _percentile);
  }

 private:
  double _percentile = 0.45;
};

void declareMax(py::module& m) {
  py::class_<MaxDummy> bld(m, "Max");
  bld.attr("__module__") = "pydp";
  bld.def(py::init<double, int, int>(), py::return_value_policy::reference,
          py::call_guard<pybind11::gil_scoped_release>());
  bld.def(py::init<double>(), py::return_value_policy::reference,
          py::call_guard<pybind11::gil_scoped_release>());
  bld.def("result", &MaxDummy::Result);
  bld.def_property("l0_sensitivity", &MaxDummy::get_l0_sensitivity,
                   &MaxDummy::set_l0_sensitivity);
  bld.def_property("linf_sensitivity", &MaxDummy::get_linf_sensitivity,
                   &MaxDummy::set_linf_sensitivity);
}

void declareMin(py::module& m) {
  py::class_<MinDummy> bld(m, "Min");
  bld.attr("__module__") = "pydp";
  bld.def(py::init<double, int, int>(), py::return_value_policy::reference,
          py::call_guard<pybind11::gil_scoped_release>());
  bld.def(py::init<double>(), py::return_value_policy::reference,
          py::call_guard<pybind11::gil_scoped_release>());
  bld.def("result", &MinDummy::Result);
  bld.def_property("l0_sensitivity", &MinDummy::get_l0_sensitivity,
                   &MinDummy::set_l0_sensitivity);
  bld.def_property("linf_sensitivity", &MinDummy::get_linf_sensitivity,
                   &MinDummy::set_linf_sensitivity);
}

void declareMedian(py::module& m) {
  py::class_<MedianDummy> bld(m, "Median");
  bld.attr("__module__") = "pydp";
  bld.def(py::init<double, int, int>(), py::return_value_policy::reference,
          py::call_guard<pybind11::gil_scoped_release>());
  bld.def(py::init<double>(), py::return_value_policy::reference,
          py::call_guard<pybind11::gil_scoped_release>());
  bld.def("result", &MedianDummy::Result);
  bld.def_property("l0_sensitivity", &MedianDummy::get_l0_sensitivity,
                   &MedianDummy::set_l0_sensitivity);
  bld.def_property("linf_sensitivity", &MedianDummy::get_linf_sensitivity,
                   &MedianDummy::set_linf_sensitivity);
}

void declarePercentile(py::module& m) {
  py::class_<PercentileDummy> bld(m, "Percentile");
  bld.attr("__module__") = "pydp";
  bld.def(py::init<double, int, int>(), py::return_value_policy::reference,
          py::call_guard<pybind11::gil_scoped_release>());
  bld.def(py::init<double>(), py::return_value_policy::reference,
          py::call_guard<pybind11::gil_scoped_release>());
  bld.def("result", &PercentileDummy::Result);
  bld.def_property("percentile", &PercentileDummy::getPercentile,
                   &PercentileDummy::setPercentile);
  bld.def_property("l0_sensitivity", &PercentileDummy::get_l0_sensitivity,
                   &PercentileDummy::set_l0_sensitivity);
  bld.def_property("linf_sensitivity", &PercentileDummy::get_linf_sensitivity,
                   &PercentileDummy::set_linf_sensitivity);
}

void init_algorithms_order_statistics(py::module& m) {
  declareMax(m);
  declareMin(m);
  declareMedian(m);
  declarePercentile(m);
}

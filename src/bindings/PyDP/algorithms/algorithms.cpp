// Provides bindings for algorithms

#include <string>

#include "../../c/c_api.h"
#include "../pydp_lib/casting.hpp"  // our caster helper library
#include "pybind11/complex.h"
#include "pybind11/functional.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include "differential_privacy/algorithms/algorithm.h"
#include "differential_privacy/algorithms/bounded-algorithm.h"
#include "differential_privacy/algorithms/bounded-mean.h"
#include "differential_privacy/algorithms/bounded-sum.h"
#include "differential_privacy/algorithms/count.h"
#include "differential_privacy/algorithms/numerical-mechanisms.h"
#include "differential_privacy/algorithms/util.h"

PYBIND11_MAKE_OPAQUE(DP_BoundedMeanInt);

using namespace std;

namespace py = pybind11;
// using namespace py::literals;

namespace dp = differential_privacy;

// template <typename T, typename std::enable_if<
//                           std::is_integral<T>::value ||
//                           std::is_floating_point<T>::value>::type* = nullptr>
// void declareBoundedSum(py::module& m, string const& suffix) {
//   py::class_<dp::BoundedSum<T>> cls(m, ("BoundedSum" + suffix).c_str());
//   py::class_<typename dp::BoundedSum<T>::Builder> bld(cls, "Builder");
//   bld.def(py::init<>());
// }

class BoundedMeanDummy {
 public:
  BoundedMeanDummy(double epsilon, int lower, int upper) {
    obj = DP_NewBoundedMean(epsilon, lower, upper);
  }

  BoundedMeanDummy(double epsilon) { obj = DP_NewBoundedMean1(epsilon); }

  double Result(py::list l) { return DP_ResultBoundedMean(obj, l); }

  ~BoundedMeanDummy() { DP_DeleteBoundedMean(obj); }

  DP_BoundedMeanInt* obj;
};

void declareBoundedMean(py::module& m) {
  py::class_<BoundedMeanDummy> bld(m, "BoundedMean");

  bld.def(py::init<double, int, int>(), py::return_value_policy::reference,
          py::call_guard<pybind11::gil_scoped_release>());
  bld.def(py::init<double>(), py::return_value_policy::reference,
          py::call_guard<pybind11::gil_scoped_release>());
  bld.def("result", &BoundedMeanDummy::Result);
  // bld.def("build", &dp::BoundedMean<T>::Builder::Build);
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

void init_algorithms(py::module& m) {
  // todo: this is the implementation of the generators we need to make work.
  // declareCount<double, std::unique_ptr<dp::LaplaceMechanism>>(m, "D");
  // declareCountBuilder<double>(m, "D");

  // from util
  m.def("xor_strings", &dp::XorStrings);
  m.def("default_epsilon", &dp::DefaultEpsilon);
  m.def("get_next_power_of_two", &dp::GetNextPowerOfTwo);
  m.def("qnorm", &dp::Qnorm);

  // py::class_<DP_BoundedMeanInt> DP_BoundedMeanInt_class(m, "DP_BoundedMeanInt");

  // m.def("_DP_NewBoundedMeanInt", DP_NewBoundedMeanInt,
  //       pybind11::return_value_policy::reference,
  //       pybind11::call_guard<pybind11::gil_scoped_release>());
  // m.def("_DP_DeleteBoundedMeanInt", DP_DeleteBoundedMeanInt,
  //       pybind11::call_guard<pybind11::gil_scoped_release>());
  // m.def("_DP_ResultBoundedMeanInt", &DP_ResultBoundedMeanInt);

  // declareAlgorithmBuilder<double, dp::BoundedSum,

  // declareBoundedSum<int>(m, "I");
  declareBoundedMean(m);
  // declareBoundedAlgorithmBuilder<int,dp::BoundedMean<int>, typename
  // dp::BoundedMean<int>::Builder>(m,"II");
}

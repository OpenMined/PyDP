// Provides bindings for Bounded Functions

#include "pybind11/complex.h"
#include "pybind11/functional.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include "algorithms/algorithm.h"
#include "algorithms/bounded-mean.h"
#include "algorithms/bounded-standard-deviation.h"
#include "algorithms/bounded-sum.h"
#include "algorithms/bounded-variance.h"
#include "base/statusor.h"

#include "../pydp_lib/algorithm_builder.hpp"
#include "../pydp_lib/casting.hpp"  // our caster helper library

using namespace std;

namespace py = pybind11;
namespace dp = differential_privacy;

template <typename T, class Algorithm>
void declareBoundedAlgorithm(py::module& m) {
  using builder = typename dp::python::AlgorithmBuilder<T, Algorithm>;
  py::class_<Algorithm> bld(m, builder().get_algorithm_name().c_str());
  bld.attr("__module__") = "pydp";
  bld.def(py::init([](double epsilon, T lower_bound, T upper_bound, int l0_sensitivity,
                      int linf_sensitivity) {
            py::print("Building with bounds");
            return builder().BuildWithBounds(epsilon, lower_bound, upper_bound,
                                             l0_sensitivity, linf_sensitivity);
          }),
          py::arg("epsilon"), py::arg("lower_bound"), py::arg("upper_bound"),
          py::arg("l0_sensitivity") = 1, py::arg("linf_sensitivity") = 1);

  bld.def(py::init([](double epsilon, int l0_sensitivity, int linf_sensitivity) {
            py::print("Building without bounds");
            return builder().BuildWithoutBounds(epsilon, l0_sensitivity,
                                                linf_sensitivity);
          }),
          py::arg("epsilon"), py::arg("l0_sensitivity") = 1,
          py::arg("linf_sensitivity") = 1);

  // TODO: can't get it work
  // bld.def_property_readonly("l0_sensitivity", [](Algorithm& obj){
  //   return obj.GetMaxPartitionsContributed();
  // });
  // bld.def_property_readonly("linf_sensitivity", [](Algorithm& obj){
  //   return obj.SetMaxContributionsPerPartition();
  // });

  bld.def("privacy_budget_left",
          [](Algorithm& obj) { return obj.RemainingPrivacyBudget(); });

  // TODO
  // bld.def("add_entries", [](Algorithm& obj, std::vector<T>& v) {
  //   return obj.AddEntries(v.begin(), v.end()).ValueOrDie();
  // });

  // bld.def("partial_result", [](Algorithm& obj) {
  //   return dp::GetValue<double>(obj.PartialResult().ValueOrDie());
  // })
  // bld.def("partial_result", [](Algorithm& obj, double privacy_budget) {
  //   return dp::GetValue<double>(obj.PartialResult(privacy_budget).ValueOrDie());
  // })

  bld.def_property_readonly("epsilon", [](Algorithm& obj) { return obj.GetEpsilon(); });

  bld.def("result", [](Algorithm& obj, std::vector<T>& v) {
    return dp::GetValue<double>(obj.Result(v.begin(), v.end()).ValueOrDie());
  });
}

void init_algorithms_bounded_functions(py::module& m) {
  declareBoundedAlgorithm<int, dp::BoundedMean<int>>(m);
  declareBoundedAlgorithm<double, dp::BoundedMean<double>>(m);

  declareBoundedAlgorithm<int, dp::BoundedSum<int>>(m);
  declareBoundedAlgorithm<double, dp::BoundedSum<double>>(m);

  declareBoundedAlgorithm<int, dp::BoundedStandardDeviation<int>>(m);
  declareBoundedAlgorithm<double, dp::BoundedStandardDeviation<double>>(m);

  declareBoundedAlgorithm<int, dp::BoundedVariance<int>>(m);
  declareBoundedAlgorithm<double, dp::BoundedVariance<double>>(m);
}

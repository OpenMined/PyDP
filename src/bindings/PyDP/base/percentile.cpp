// Provides bindings for percentile class

#include "pybind11/pybind11.h"

#include "base/percentile.h"

using namespace std;
namespace py = pybind11;
namespace dpb = differential_privacy::base;

template <typename T>
void declarePercentile(py::module& m, string const& suffix) {
  py::class_<dpb::Percentile<T>>(m, ("Percentile" + suffix).c_str())
      .def(py::init())
      .def("add", &dpb::Percentile<T>::Add)
      .def("reset", &dpb::Percentile<T>::Reset)
      .def("serialize_to_proto", &dpb::Percentile<T>::SerializeToProto)
      .def("merge_from_proton", &dpb::Percentile<T>::MergeFromProto)
      .def("memory", &dpb::Percentile<T>::Memory)
      .def("num_values", &dpb::Percentile<T>::num_values)
      .def("get_relative_rank", &dpb::Percentile<T>::GetRelativeRank);
}

void init_base_percentile(py::module& m) {
  declarePercentile<int>(m, "Int");
  declarePercentile<double>(m, "Double");
}

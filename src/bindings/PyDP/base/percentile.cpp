// Provides bindings for percentile class

#include "pybind11/pybind11.h"

#include "differential_privacy/base/percentile.h"

using namespace std;
namespace py = pybind11;
namespace dpbase = differential_privacy::base;

template <typename T>
void declarePercentile(py::module& m, string const& suffix) {
  py::class_<dpbase::Percentile<T>>(m, ("Percentile" + suffix).c_str())
      .def(py::init())
      .def("add", &dpbase::Percentile<T>::Add)
      .def("reset", &dpbase::Percentile<T>::Reset)
      .def("serialize_to_proto", &dpbase::Percentile<T>::SerializeToProto)
      .def("merge_from_proton", &dpbase::Percentile<T>::MergeFromProto)
      .def("memory", &dpbase::Percentile<T>::Memory)
      .def("num_values", &dpbase::Percentile<T>::num_values)
      .def("get_relative_rank", &dpbase::Percentile<T>::GetRelativeRank);
}

void init_base_percentile(py::module& m) {
  declarePercentile<int>(m, "Int");
  declarePercentile<double>(m, "Double");
}

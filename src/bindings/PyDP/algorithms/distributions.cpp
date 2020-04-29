// Provides bindings for distributions

#include "pybind11/pybind11.h"

#include "differential_privacy/algorithms/distributions.h"

using namespace std;
namespace py = pybind11;
namespace dpinternal = differential_privacy::internal;

void declareLaplaceDistribution(py::module& m) {
  py::class_<dpinternal::LaplaceDistribution>(m, "LaplaceDistribution")
      .def(py::init<double>())
      .def("get_uniform_double", &dpinternal::LaplaceDistribution::GetUniformDouble)
      .def("sample",
           (double (dpinternal::LaplaceDistribution::*)()) & dpinternal::LaplaceDistribution::Sample)
      .def("sample", (double (dpinternal::LaplaceDistribution::*)(double)) &
                         dpinternal::LaplaceDistribution::Sample)
      .def("get_diversity", &dpinternal::LaplaceDistribution::GetDiversity)
      .def("cdf", &dpinternal::LaplaceDistribution::cdf);
}

void declareGaussianDistribution(py::module& m) {
  py::class_<dpinternal::GaussianDistribution>(m, "GaussianDistribution")
      .def(py::init<double>())
      .def("sample", (double (dpinternal::GaussianDistribution::*)()) &
                         dpinternal::GaussianDistribution::Sample)
      .def("sample", (double (dpinternal::GaussianDistribution::*)(double)) &
                         dpinternal::GaussianDistribution::Sample)
      .def("stddev", &dpinternal::GaussianDistribution::Stddev);
}

void init_algorithms_distributions(py::module& m) {
  declareLaplaceDistribution(m);
  declareGaussianDistribution(m);
}

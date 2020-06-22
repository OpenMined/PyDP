// Provides bindings for distributions

#include "pybind11/pybind11.h"

#include "algorithms/distributions.h"

using namespace std;
namespace py = pybind11;
namespace dpi = differential_privacy::internal;

void declareLaplaceDistribution(py::module& m) {
  py::class_<dpi::LaplaceDistribution> laplace_dist(m, "LaplaceDistribution");
  laplace_dist.attr("__module__") = "pydp";
  laplace_dist.def(py::init<double>())
      .def("get_uniform_double", &dpi::LaplaceDistribution::GetUniformDouble)
      .def("sample",
           (double (dpi::LaplaceDistribution::*)()) & dpi::LaplaceDistribution::Sample)
      .def("sample", (double (dpi::LaplaceDistribution::*)(double)) &
                         dpi::LaplaceDistribution::Sample)
      .def("get_diversity", &dpi::LaplaceDistribution::GetDiversity)
      .def("cdf", &dpi::LaplaceDistribution::cdf);
}

void declareGaussianDistribution(py::module& m) {
  py::class_<dpi::GaussianDistribution> gauss_dist(m, "GaussianDistribution");
  gauss_dist.attr("__module__") = "pydp";
  gauss_dist.def(py::init<double>())
      .def("sample", (double (dpi::GaussianDistribution::*)()) &
                         dpi::GaussianDistribution::Sample)
      .def("sample", (double (dpi::GaussianDistribution::*)(double)) &
                         dpi::GaussianDistribution::Sample)
      .def("stddev", &dpi::GaussianDistribution::Stddev);
}

void init_algorithms_distributions(py::module& m) {
  declareLaplaceDistribution(m);
  declareGaussianDistribution(m);
}

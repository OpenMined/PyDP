// Provides bindings for distributions

#include "pybind11/pybind11.h"

#include "differential_privacy/algorithms/distributions.h"

using namespace std;
namespace py = pybind11;
namespace dpi = differential_privacy::internal;

void declareLaplaceDistribution(py::module& m) {
  py::class_<dpi::LaplaceDistribution>(m, "LaplaceDistribution")
      .def(py::init<double>())
      .def("GetUniformDouble", &dpi::LaplaceDistribution::GetUniformDouble)
      .def("Sample",
           (double (dpi::LaplaceDistribution::*)()) & dpi::LaplaceDistribution::Sample)
      .def("Sample", (double (dpi::LaplaceDistribution::*)(double)) &
                         dpi::LaplaceDistribution::Sample)
      .def("GetDiversity", &dpi::LaplaceDistribution::GetDiversity)
      .def("cdf", &dpi::LaplaceDistribution::cdf);
}

void declareGaussianDistribution(py::module& m) {
  py::class_<dpi::GaussianDistribution>(m, "GaussianDistribution")
      .def(py::init<double>())
      .def("Sample", (double (dpi::GaussianDistribution::*)()) &
                         dpi::GaussianDistribution::Sample)
      .def("Sample", (double (dpi::GaussianDistribution::*)(double)) &
                         dpi::GaussianDistribution::Sample)
      .def("Stddev", &dpi::GaussianDistribution::Stddev);
}

void init_distributions(py::module& m) {
  declareLaplaceDistribution(m);
  declareGaussianDistribution(m);
}

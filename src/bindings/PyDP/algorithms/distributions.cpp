// Provides bindings for distributions
#include "pybind11/pybind11.h"

#include "algorithms/distributions.h"

using namespace std;
namespace py = pybind11;
namespace dpi = differential_privacy::internal;

void declareLaplaceDistribution(py::module &m) {
  py::class_<dpi::LaplaceDistribution> laplace_dist(m, "LaplaceDistribution");
  laplace_dist.attr("__module__") = "pydp";
  laplace_dist
      .def(py::init<double, double>(), py::arg("epsilon") = 0., py::arg("sensitivity"))
      .def("get_uniform_double", &dpi::LaplaceDistribution::GetUniformDouble,
           R"pbdoc(Returns a uniform random integer of in range [0, 2^53).)pbdoc")
      .def("sample", py::overload_cast<double>(&dpi::LaplaceDistribution::Sample),
           py::arg("scale") = 1.0,
           R"pbdoc(
                    Samples the Laplacian distribution Laplace(u, scale*b).

                    Parameters
                    ----------
                    scale
                         A factor to scale b.
               )pbdoc");
  laplace_dist.def("get_diversity", &dpi::LaplaceDistribution::GetDiversity,
                   R"pbdoc(
               Returns the parameter defining this distribution, often labeled b.

          )pbdoc");
  laplace_dist.attr("__doc__") = "Draws samples from the Laplacian distribution.";
}

void declareGaussianDistribution(py::module &m) {
  py::class_<dpi::GaussianDistribution> gauss_dist(m, "GaussianDistribution");
  gauss_dist.attr("__module__") = "pydp";
  gauss_dist.def(py::init<double>())
      .def("sample", py::overload_cast<double>(&dpi::GaussianDistribution::Sample),
           py::arg("scale") = 1.0,
           R"pbdoc(Samples the Gaussian with distribution Gauss(scale*stddev).
                    Parameters
                    ----------
                    scale
                         A factor to scale stddev.
             )pbdoc")
      .def_property_readonly("stddev", &dpi::GaussianDistribution::Stddev,
                             R"pbdoc(Returns stddev)pbdoc");
}

void declareGeometricDistribution(py::module &m) {
  py::class_<dpi::GeometricDistribution> geometric_dist(m, "GeometricDistribution");
  geometric_dist.attr("__module__") = "pydp";
  geometric_dist
      .def(py::init<double>(), py::arg("lambda_"),
           "Constructs a GeometricDistribution, p = 1 - e^-lambda.")
      .def("get_uniform_double", &dpi::GeometricDistribution::GetUniformDouble)

      .def("sample", py::overload_cast<double>(&dpi::GeometricDistribution::Sample),
           py::arg("scale") = 1.0, "Returns a sample from p = 1 - e^-(lambda/scale).")

      .def_property_readonly("lambda", &dpi::GeometricDistribution::Lambda,
                             R"pbdoc(Returns lambda. Where p = 1 - e^-lambda)pbdoc");
  geometric_dist.attr("__doc__") =
      R"pbdoc(Draws samples from the geometric distribution of probability
          \math{p = 1 - e^{-\lambda}}, i.e. the number of bernoulli trial failures
before the first success where the success probability is as defined above. lambda must
          be positive. If the result would be higher than the maximum int64_t, returns
          the maximum int64_t, which means that users should be careful around the edges
          of their distribution)pbdoc";
}

void init_algorithms_distributions(py::module &m) {
  declareLaplaceDistribution(m);
  declareGaussianDistribution(m);
  declareGeometricDistribution(m);
}

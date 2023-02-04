// Provides bindings for distributions
#include "pybind11/pybind11.h"

#include "algorithms/distributions.h"

namespace py = pybind11;
namespace dpi = differential_privacy::internal;

class declareLaplaceDistributionClass {
 public:
  std::unique_ptr<dpi::LaplaceDistribution> build(double epsilon, double sensitivity) {
    dpi::LaplaceDistribution::Builder builder;
    builder.SetEpsilon(epsilon);
    builder.SetSensitivity(sensitivity);
    return std::move(builder.Build().value());
  };
  void declareLaplaceDistribution(py::module &m) {
    py::class_<dpi::LaplaceDistribution> laplace_dist(m, "LaplaceDistribution");
    laplace_dist.attr("__module__") = "pydp";
    laplace_dist
        .def(py::init([this](double epsilon, double sensitivity) {
               return this->build(epsilon, sensitivity);
             }),
             py::arg("epsilon") = 0., py::arg("sensitivity"))
        .def("get_uniform_double", &dpi::LaplaceDistribution::GetUniformDouble,
             R"pbdoc(Returns a uniform random integer of in range [0, 2^53).)pbdoc")
        .def("sample", &dpi::LaplaceDistribution::Sample,
             R"pbdoc(
                         Samples the Laplacian distribution Laplace(u, b).
                        
                    )pbdoc");
    laplace_dist.def("get_diversity", &dpi::LaplaceDistribution::GetDiversity,
                     R"pbdoc(
                    Returns the parameter defining this distribution, often labeled b.

               )pbdoc");
    laplace_dist.attr("__doc__") = "Draws samples from the Laplacian distribution.";
  }
};

class declareGaussianDistributionClass {
 public:
  std::unique_ptr<dpi::GaussianDistribution> build(double stddev) {
    dpi::GaussianDistribution::Builder builder;
    builder.SetStddev(stddev);
    return std::move(builder.Build().value());
  };
  void declareGaussianDistribution(py::module &m) {
    py::class_<dpi::GaussianDistribution> gauss_dist(m, "GaussianDistribution");

    gauss_dist.attr("__module__") = "pydp";
    gauss_dist
        .def(py::init([this](double stddev) { return this->build(stddev); }),
             py::arg("epsilon"))
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
};

class declareGeometricDistributionClass {
 public:
  std::unique_ptr<dpi::GeometricDistribution> build(double lambda_) {
    dpi::GeometricDistribution::Builder builder;
    builder.SetLambda(lambda_);
    return std::move(builder.Build().value());
  };
  void declareGeometricDistribution(py::module &m) {
    py::class_<dpi::GeometricDistribution> geometric_dist(m, "GeometricDistribution");
    geometric_dist.attr("__module__") = "pydp";
    geometric_dist
        .def(py::init([this](double lambda_) { return this->build(lambda_); }),
             py::arg("lambda_"),
             "Constructs a GeometricDistribution, p = 1 - e^-lambda_.")
        .def("get_uniform_double", &dpi::GeometricDistribution::GetUniformDouble)

        .def("sample", py::overload_cast<double>(&dpi::GeometricDistribution::Sample),
             py::arg("scale") = 1.0,
             "Returns a sample from p = 1 - e^-(lambda_/scale).")

        .def_property_readonly(
            "lambda_", &dpi::GeometricDistribution::Lambda,
            R"pbdoc(Returns lambda_. Where p = 1 - e^-lambda_)pbdoc");
    geometric_dist.attr("__doc__") =
        R"pbdoc(Draws samples from the geometric distribution of probability
               \math{p = 1 - e^{-\lambda_}}, i.e. the number of bernoulli trial failures
     before the first success where the success probability is as defined above. lambda_ must
               be positive. If the result would be higher than the maximum int64_t, returns
               the maximum int64_t, which means that users should be careful around the edges
               of their distribution)pbdoc";
  }
};

void init_algorithms_distributions(py::module &m) {
  declareLaplaceDistributionClass laplace_obj = declareLaplaceDistributionClass();
  laplace_obj.declareLaplaceDistribution(m);
  declareGaussianDistributionClass gaussian_obj = declareGaussianDistributionClass();
  gaussian_obj.declareGaussianDistribution(m);
  declareGeometricDistributionClass geom_obj = declareGeometricDistributionClass();
  geom_obj.declareGeometricDistribution(m);
}

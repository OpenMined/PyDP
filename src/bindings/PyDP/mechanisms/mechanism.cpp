// Provides bindings for distributions
#include "pybind11/pybind11.h"

#include "algorithms/numerical_mechanism.h"

using namespace std;
namespace py = pybind11;
namespace dp = differential_privacy;

class declareLaplaceDistributionClass {
 public:
  std::unique_ptr<dp::LaplaceDistribution> build(double epsilon, std::optional<double> sensitivity= std::nullopt) {
    dp::LaplaceDistribution::Builder builder;
    builder.SetEpsilon(epsilon);
    if (sensitivity.has_value())
      builder.SetMaxPartitionsContributed(l0sensitivity.value());
    if (sensitivity){
    builder.SetSensitivity(sensitivity.value());
    }
    return std::move(builder.Build().value());
  };
  void declareLaplaceDistribution(py::module &m) {
    py::class_<dp::LaplaceDistribution> laplace_dist(m, "LaplaceDistribution");
    laplace_dist.attr("__module__") = "pydp";
    laplace_dist
        .def(py::init([this](double epsilon, double sensitivity) {
               return this->build(epsilon, sensitivity);
             }),
             py::arg("epsilon") = 0., py::arg("sensitivity"))
        .def("get_uniform_double", &dp::LaplaceDistribution::GetUniformDouble,
             R"pbdoc(Returns a uniform random integer of in range [0, 2^53).)pbdoc")
        .def("sample", py::overload_cast<double>(&dp::LaplaceDistribution::Sample),
             py::arg("scale") = 1.0,
             R"pbdoc(
                         Samples the Laplacian distribution Laplace(u, scale*b).

                         Parameters
                         ----------
                         scale
                              A factor to scale b.
                    )pbdoc");
    laplace_dist.def("get_diversity", &dp::LaplaceDistribution::GetDiversity,
                     R"pbdoc(
                    Returns the parameter defining this distribution, often labeled b.

               )pbdoc");
    laplace_dist.attr("__doc__") = "Draws samples from the Laplacian distribution.";
  }
};

class declareGaussianDistributionClass {
 public:
  std::unique_ptr<dp::GaussianDistribution> build(double stddev) {
    dp::GaussianDistribution::Builder builder;
    builder.SetStddev(stddev);
    return std::move(builder.Build().value());
  };
  void declareGaussianDistribution(py::module &m) {
    py::class_<dp::GaussianDistribution> gauss_dist(m, "GaussianDistribution");

    gauss_dist.attr("__module__") = "pydp";
    gauss_dist
        .def(py::init([this](double stddev) { return this->build(stddev); }),
             py::arg("epsilon"))
        .def("sample", py::overload_cast<double>(&dp::GaussianDistribution::Sample),
             py::arg("scale") = 1.0,
             R"pbdoc(Samples the Gaussian with distribution Gauss(scale*stddev).
                              Parameters
                              ----------
                              scale
                                   A factor to scale stddev.
                    )pbdoc")
        .def_property_readonly("stddev", &dp::GaussianDistribution::Stddev,
                               R"pbdoc(Returns stddev)pbdoc");
  }
};

class declareGeometricDistributionClass {
 public:
  std::unique_ptr<dp::GeometricDistribution> build(double lambda) {
    dp::GeometricDistribution::Builder builder;
    builder.SetLambda(lambda);
    return std::move(builder.Build().value());
  };
  void declareGeometricDistribution(py::module &m) {
    py::class_<dp::GeometricDistribution> geometric_dist(m, "GeometricDistribution");
    geometric_dist.attr("__module__") = "pydp";
    geometric_dist
        .def(py::init([this](double lambda) { return this->build(lambda); }),
             py::arg("lambda"),
             "Constructs a GeometricDistribution, p = 1 - e^-lambda.")
        .def("get_uniform_double", &dp::GeometricDistribution::GetUniformDouble)

        .def("sample", py::overload_cast<double>(&dp::GeometricDistribution::Sample),
             py::arg("scale") = 1.0, "Returns a sample from p = 1 - e^-(lambda/scale).")

        .def_property_readonly("lambda", &dp::GeometricDistribution::Lambda,
                               R"pbdoc(Returns lambda. Where p = 1 - e^-lambda)pbdoc");
    geometric_dist.attr("__doc__") =
        R"pbdoc(Draws samples from the geometric distribution of probability
               \math{p = 1 - e^{-\lambda}}, i.e. the number of bernoulli trial failures
     before the first success where the success probability is as defined above. lambda must
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

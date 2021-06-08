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


void init_algorithms_distributions(py::module &m) {
  declareLaplaceDistributionClass laplace_obj = declareLaplaceDistributionClass();
  laplace_obj.declareLaplaceDistribution(m);
  declareGaussianDistributionClass gaussian_obj = declareGaussianDistributionClass();
  gaussian_obj.declareGaussianDistribution(m);
  declareGeometricDistributionClass geom_obj = declareGeometricDistributionClass();
  geom_obj.declareGeometricDistribution(m);
}

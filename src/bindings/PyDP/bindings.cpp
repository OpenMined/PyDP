#include "pybind11/embed.h"

using namespace std;

namespace py = pybind11;

// base
void init_base_status(py::module &);
void init_base_logging(py::module &);

// bounded functions
void init_algorithms_bounded_functions(py::module &);
void init_algorithms_count(py::module &);

void init_algorithms_partition_selection_strategies(py::module &);

// util
void init_algorithms_util(py::module &);

// distributions
void init_algorithms_distributions(py::module &);

// order statistics
void init_algorithms_order_statistics(py::module &);

// rand
void init_algorithms_rand(py::module &);

// proto
void init_proto(py::module &);

PYBIND11_MODULE(_pydp, m) {
  m.doc() = "Google Differential Privacy python extension";

  // Base
  init_base_status(m);
  init_base_logging(m);

  // Algorithms
  auto malgorithms = m.def_submodule("_algorithms");
  init_algorithms_bounded_functions(malgorithms);
  init_algorithms_count(malgorithms);
  init_algorithms_order_statistics(malgorithms);
  init_algorithms_partition_selection_strategies(malgorithms);

  auto mdistributions = m.def_submodule("_distributions");
  init_algorithms_distributions(mdistributions);

  auto mutil = m.def_submodule("_util", "Some Utility Functions");
  init_algorithms_rand(mutil);
  init_algorithms_util(mutil);

  // Proto
  // TODO: Delete if it is not necessary (we no longer return StatusOr to the user)
  init_proto(m);
}

#include <fstream>
#include <string>

#include "pybind11/pybind11.h"

#include "proto/summary.pb.h"

using namespace std;

namespace py = pybind11;
using namespace py::literals;

namespace dp = differential_privacy;

void init_proto(py::module &m) {
  py::class_<dp::Output> output(m, "Output");
  output.def(py::init());

  // Add save and load functions to use protobuf serde in tests
  py::class_<dp::Summary>(m, "Summary")
      .def(py::init())
      .def("save",
           [](dp::Summary &pythis, std::string &filename) {
             fstream output(filename, ios::out | ios::trunc | ios::binary);
             pythis.SerializeToOstream(&output);
           })
      .def("load", [](dp::Summary &pythis, std::string &filename) {
        fstream input(filename, ios::in | ios::binary);
        pythis.ParseFromIstream(&input);
      });
}

#include <fstream>
#include <string>

#include "pybind11/pybind11.h"

#include "proto/data.pb.h"
#include "proto/summary.pb.h"

namespace py = pybind11;
namespace dp = differential_privacy;

void init_proto(py::module &m) {
  py::class_<dp::Output> output(m, "Output");
  output.def(py::init());

  // Add save and load functions to use protobuf serde in tests
  py::class_<dp::Summary>(m, "Summary")
      .def(py::init())
      .def("save",
           [](dp::Summary &pythis, std::string &filename) {
             std::fstream output(filename,
                                 std::ios::out | std::ios::trunc | std::ios::binary);
             pythis.SerializeToOstream(&output);
           })
      .def("load",
           [](dp::Summary &pythis, std::string &filename) {
             std::fstream input(filename, std::ios::in | std::ios::binary);
             pythis.ParseFromIstream(&input);
           })
      .def("to_bytes", [](dp::Summary &pythis) {
        std::string serialization;
        pythis.SerializeToString(&serialization);
        return py::bytes(serialization);
      });

  m.def(
      "bytes_to_summary",
      [](const py::bytes &bytes) {
        dp::Summary result;
        result.ParseFromString(bytes);
        return result;
      },
      py::arg("bytes"));
}

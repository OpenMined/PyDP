#include "../../c/c_api.h"
#include "pybind11/complex.h"
#include "pybind11/functional.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

PYBIND11_MAKE_OPAQUE(BoundedFunctionHelperObject);

using namespace std;

namespace py = pybind11;

class Dummy {
 public:
  Dummy(double epsilon, int lower, int upper) {
    obj = NewBoundedFunctionObject(epsilon, lower, upper);
  }

  Dummy(double epsilon) {
    obj = NewBoundedFunctionObject1(epsilon);
  }

  virtual double Result(py::list){return 0.0;}

  virtual double Result(py::list, double) {return 0.0;}

  ~Dummy() {
    DeleteBoundedFunctionObject(obj);
  }

  BoundedFunctionHelperObject* obj;
};
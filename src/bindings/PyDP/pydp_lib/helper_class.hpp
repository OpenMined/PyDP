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
  Dummy(double epsilon, int lower_bound, int upper_bound) {
    obj = NewBoundedFunctionObject(epsilon, lower_bound, upper_bound);
  }

  Dummy(double epsilon) {
    obj = NewBoundedFunctionObject1(epsilon);
  }

  void set_l0_sensitivity(int _l0_sensitivity) {
    set_l0_sensitivity_(_l0_sensitivity);
  }
  int get_l0_sensitivity() {
    return get_l0_sensitivity_();
  }

  void set_linf_sensitivity(int _linf_sensitivity) {
    set_linf_sensitivity_(_linf_sensitivity);
  }
  int get_linf_sensitivity() {
    return get_linf_sensitivity_();
  }

  virtual double Result(py::list) {}

  virtual double Result(py::list, double) {}

  ~Dummy() {
    DeleteBoundedFunctionObject(obj);
  }

  BoundedFunctionHelperObject* obj;
};
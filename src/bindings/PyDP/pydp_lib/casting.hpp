// Convenient place to store type casters that are used through out project
// This teaches pybind11 to cast types provided in the absl library

#include "absl/strings/string_view.h"
#include "absl/types/optional.h"
#include "pybind11/stl.h"

namespace pybind11 {
namespace detail {
// incase we use this

}  // namespace detail
}  // namespace pybind11

// Convenient place to store type casters that are used through out project
// This teaches pybind11 to cast types provided in the absl library


#include "pybind11/stl.h"
#include "absl/strings/string_view.h"
#include "absl/types/optional.h"

namespace pybind11 {
    namespace detail
    {
        template <>
        struct type_caster<absl::string_view> : string_caster<absl::string_view, true> {};

        template <typename T>
        struct type_caster<absl::optional<T>> : optional_caster<absl::optional<T>> {};
    }   
}
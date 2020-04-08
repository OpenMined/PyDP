// Convenient place to store type casters that are used through out project
// This teaches pybind11 to cast types provided in the absl library


#include "pybind11/stl.h"
#include "absl/strings/string_view.h"
#include "absl/types/optional.h"

#include "differential_privacy/algorithms/bounded-mean.h"

namespace pybind11 {
    namespace detail
    {
        template <>
        struct type_caster<absl::string_view> : string_caster<absl::string_view, true> {};

        template <typename T>
        struct type_caster<absl::optional<T>> : optional_caster<absl::optional<T>> {};


      // It compiles but it's probably completely useless:
      template <typename T>
       struct type_caster<std::unique_ptr<differential_privacy::BoundedMean<T>>> {
         static handle cast(std::unique_ptr<differential_privacy::BoundedMean<T>> src, return_value_policy /* policy */, handle /* parent */) {
           return static_cast<typename differential_privacy::BoundedMean<T>>(*src);
         };
      };

    }
}

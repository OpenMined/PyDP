include(FetchContent)

FetchContent_Declare(
  google_dp
  GIT_REPOSITORY https://github.com/google/differential-privacy.git
  GIT_TAG        main
)

FetchContent_MakeAvailable(google_dp)

FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG        v3.0.1
)

FetchContent_MakeAvailable(pybind11)

FetchContent_Declare(
  abseil-cpp
  GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git
  GIT_TAG         20250512.1
)
FetchContent_MakeAvailable(abseil-cpp)

pybind11_add_module(_pydp bindings.cpp algorithms/bounded_functions.cpp 
algorithms/count.cpp  algorithms/distributions.cpp  algorithms/order_statistics.cpp  
algorithms/partition_selection_strategies.cpp  algorithms/qunatile_tree.cpp  algorithms/rand.cpp  
algorithms/util.cpp mechanisms/mechanism.cpp proto/proto.cpp)

target_link_libraries(_pydp PUBLIC dp_algorithms dp_protos
    absl::base
    absl::check        
    absl::status
    absl::statusor
    absl::strings
    absl::flat_hash_set
)

target_compile_options(_pydp PRIVATE -Wno-deprecated-declarations)
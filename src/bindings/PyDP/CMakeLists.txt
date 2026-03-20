include(FetchContent)

FetchContent_Declare(
  google_dp
  GIT_REPOSITORY https://github.com/google/differential-privacy.git
  GIT_TAG        8c7aac224465468407b4f9e11d3fb5ce90a15d58 # Sep 5, 2025
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

# Add compiler flags for build optimization
if (APPLE)
    message(STATUS "Building on macOS, enabling macOS-specific flags.")
    # Removed aggressive -Oz optimization and -dead_strip as they override linker logic
    # and cause critical Python dynamic lookup symbol stripping under pybind.
elseif (UNIX)
    message(STATUS "Building on Linux, enabling Linux-specific flags.")
    # For Linux, use -Oz and garbage collection
   set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Oz -s -flto -Wl,--gc-sections")
else()
    message(WARNING "Unsupported platform. No size optimization flags applied.")
endif()


pybind11_add_module(_pydp bindings.cpp algorithms/bounded_functions.cpp 
algorithms/count.cpp  algorithms/distributions.cpp  algorithms/order_statistics.cpp  
algorithms/partition_selection_strategies.cpp  algorithms/qunatile_tree.cpp  algorithms/rand.cpp  
algorithms/util.cpp mechanisms/mechanism.cpp proto/proto.cpp)

set(PYDP_DEPS 
    dp_algorithms dp_protos
    absl::base
    absl::spinlock_wait
    absl::check  
    absl::hash    
    absl::status
    absl::statusor
    absl::strings
    absl::strings_internal
    absl::flat_hash_set    
    absl::raw_logging_internal
    absl::log_internal_message
    absl::log_internal_check_op
    absl::log_globals
    absl::log
    absl::log_internal_nullguard
    absl::log_internal_globals
    absl::raw_hash_set
    absl::str_format_internal
    absl::throw_delegate
)

target_link_libraries(_pydp PUBLIC ${PYDP_DEPS})

if(NOT WIN32)
  target_compile_options(_pydp PRIVATE -Wno-deprecated-declarations)
endif()

# Force the Apple macOS linker to bake in all Google DP/Abseil static archive symbols statically.
# This decisively bypasses the '-undefined dynamic_lookup' flat namespace symbol stripping!
# This restricts the force loading behavior exclusively to macOS using generator expressions,
# keeping the native interface targets mapped without incurring duplicate link evaluations.
target_link_options(_pydp PRIVATE 
    "$<$<PLATFORM_ID:Darwin>:-Wl,-force_load,$<TARGET_FILE:dp_algorithms>>"
    "$<$<PLATFORM_ID:Darwin>:-Wl,-force_load,$<TARGET_FILE:dp_protos>>"
    "$<$<PLATFORM_ID:Darwin>:-Wl,-force_load,$<TARGET_FILE:absl::strings_internal>>"
    "$<$<PLATFORM_ID:Darwin>:-Wl,-force_load,$<TARGET_FILE:absl::raw_hash_set>>"
    "$<$<PLATFORM_ID:Darwin>:-Wl,-force_load,$<TARGET_FILE:absl::str_format_internal>>"
    "$<$<PLATFORM_ID:Darwin>:-Wl,-force_load,$<TARGET_FILE:absl::throw_delegate>>"
    "$<$<PLATFORM_ID:Darwin>:-Wl,-force_load,$<TARGET_FILE:absl::spinlock_wait>>"
)

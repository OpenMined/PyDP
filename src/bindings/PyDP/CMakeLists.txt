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
    # For macOS, use -Oz and dead-code stripping
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Oz")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-dead_strip")
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

target_link_libraries(_pydp PUBLIC dp_algorithms dp_protos
    absl::base
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
)

if(NOT WIN32)
  target_compile_options(_pydp PRIVATE -Wno-deprecated-declarations -Wdeprecated-declarations)
endif()

# Force the Apple macOS linker to bake in all Google DP/Abseil static archive symbols statically.
# This decisively bypasses the '-undefined dynamic_lookup' flat namespace symbol stripping!
if(APPLE)
  set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,-all_load")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-all_load")
endif()

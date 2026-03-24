cmake_minimum_required(VERSION 3.16)
project(PyDP LANGUAGES CXX)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
# Force Protobuf to build with dynamic runtime (/MD)
set(protobuf_BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
set(protobuf_MSVC_STATIC_RUNTIME OFF CACHE BOOL "" FORCE)

# Force Abseil to use dynamic runtime if it has a toggle
set(ABSL_PROPAGATE_CXX_STD ON CACHE BOOL "" FORCE)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(src/bindings/PyDP)

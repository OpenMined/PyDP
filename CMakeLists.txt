cmake_minimum_required(VERSION 3.16)
project(PyDP LANGUAGES CXX)

# 1. Keep MSVC runtime Dynamic (Python standard)
# set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# 2. Force third-party libraries to be built statically so they are baked into the wheel
# set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
# 1. Globally tell CMake to prefer static libraries over shared DLLs
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries" FORCE)
set(OPENSSL_USE_STATIC_LIBS TRUE)

# 2. Specifically override Protobuf/Abseil if they ignore BUILD_SHARED_LIBS
set(protobuf_BUILD_SHARED_LIBS OFF CACHE BOOL "Build protobuf as static" FORCE)
set(protobuf_MSVC_STATIC_RUNTIME ON CACHE BOOL "Use /MT for protobuf" FORCE)

set(ABSL_MSVC_STATIC_RUNTIME ON CACHE BOOL "Force Abseil to use /MT" FORCE)
set(ABSL_PROPAGATE_CXX_STD ON CACHE BOOL "" FORCE)
#set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries" FORCE)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(src/bindings/PyDP)

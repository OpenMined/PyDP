cmake_minimum_required(VERSION 3.16)
project(PyDP LANGUAGES CXX)

# 1. Keep MSVC runtime Dynamic (Python standard)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

# 2. Force third-party libraries to be built statically so they are baked into the wheel
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(src/bindings/PyDP)

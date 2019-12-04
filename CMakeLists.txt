cmake_minimum_required(VERSION 2.8.12)
project(pydp)

add_subdirectory(differential-privacy)

add_subdirectory(third_party/abseil-cpp)

add_subdirectory(third_party/protobuf/cmake)
add_subdirectory(third_party/boringssl)
add_subdirectory(Pybind11)
# pybind11_add_module(cmake_example src/main.cpp)



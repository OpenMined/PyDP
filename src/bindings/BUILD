load("//third_party/pybind11_bazel:build_defs.bzl", "pybind_extension")

pybind_extension(
    name = "PyDP",
    srcs = glob([
        "PyDP/*.cpp",
        "PyDP/base/*.cpp"
    ]),
    visibility = ["//src/python:__pkg__"],
    deps = [
        "@google_dp//differential_privacy/base:status",
        "@google_dp//differential_privacy/base:statusor"
    ],
)

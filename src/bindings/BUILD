load("@pybind11_bazel//:build_defs.bzl", "pybind_extension")

pybind_extension(
    name = "pydp",
    srcs = glob([
        "PyDP/*.cpp",
        "PyDP/base/*.cpp",
        "PyDP/algorithms/*.cpp",
        "PyDP/algorithms/*.cpp",
        "PyDP/pydp_lib/*.hpp",
        "PyDP/proto/*.cpp",
        "c/*.cc",
        "c/*.h"
    ]),

    visibility = ["//src/python:__pkg__"],
    deps = [
        "@google_dp//base:percentile",
        "@google_dp//base:logging",
        "@google_dp//base:statusor_internals",
        "@google_dp//base:status",
        "@google_dp//base:canonical_errors",
        "@google_dp//base:statusor",
        "@google_dp//algorithms:algorithm",
        "@google_dp//algorithms:bounded-mean",
        "@google_dp//algorithms:bounded-sum",
        "@google_dp//algorithms:bounded-standard-deviation",
        "@google_dp//algorithms:count",
        "@google_dp//algorithms:order-statistics",
        "@google_dp//proto:util-lib"
    ],
)
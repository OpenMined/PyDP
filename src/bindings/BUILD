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
# Windows support. Note: Needs a patch to logging.cc in third_party\differential-privacy\cc\base\logging.cc
# Copy: patched_logging.cc to third_party\differential-privacy\cc\base\logging.cc

pybind_extension(
    name = "pydp-win",
    srcs = glob([
        "PyDP/*.cpp",
        "PyDP/base/logging.cpp",
        "PyDP/base/status.cpp",
        "PyDP/base/percentile.cpp",

        "PyDP/algorithms/count.cpp",
        "PyDP/algorithms/util.cpp",
        "c/*.cc",
        "c/*.h",
    ]),

    features = ["windows_export_all_symbols", "win_def_file"],
    linkopts =["/VERBOSE:CLR"],
    copts = ["/DCOMPILING_DLL", "/MD", "/EHsc", "/c"],
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
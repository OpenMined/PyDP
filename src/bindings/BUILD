load("@pybind11_bazel//:build_defs.bzl", "pybind_extension")

pybind_extension(
    name = "_pydp",
    srcs = glob([
        "PyDP/*.cpp",
        "PyDP/base/*.cpp",
        "PyDP/algorithms/*.cpp",
        "PyDP/pydp_lib/*.hpp",
        "PyDP/proto/*.cpp",
        "PyDP/mechanisms/*.cpp"
    ]),

    visibility = ["//src/python:__pkg__"],
    deps = [
        "@com_google_cc_differential_privacy//base:percentile",
        "@com_google_cc_differential_privacy//base:logging",
        "@com_google_cc_differential_privacy//base:statusor_internals",
        "@com_google_cc_differential_privacy//base:status",
        # "@com_google_cc_differential_privacy//base:canonical_errors",
        "@com_google_cc_differential_privacy//base:statusor",
        "@com_google_cc_differential_privacy//algorithms:algorithm",
        "@com_google_cc_differential_privacy//algorithms:bounded-mean",
        "@com_google_cc_differential_privacy//algorithms:bounded-sum",
        "@com_google_cc_differential_privacy//algorithms:bounded-standard-deviation",
        "@com_google_cc_differential_privacy//algorithms:partition-selection",
        "@com_google_cc_differential_privacy//algorithms:numerical-mechanisms",
        "@com_google_cc_differential_privacy//algorithms:count",
        "@com_google_cc_differential_privacy//algorithms:order-statistics",
        "@com_google_cc_differential_privacy//proto:util-lib"
    ],
)

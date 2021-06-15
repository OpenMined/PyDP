load("@rules_python//python:defs.bzl", "py_library")

py_library(
    name = "_pydp_algo",
    srcs = glob([
        "*.py",
        "algorithms/*.py",
        "algorithms/*/*.py",
        "distributions/*.py",
        "utils/*.py",
        "ml/*.py",
        "ml/*/*.py",
    ]),
    visibility = ["//src/python:__pkg__"],
)

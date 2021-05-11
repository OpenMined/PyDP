load("@rules_python//python:defs.bzl", "py_binary")

py_binary(
    name = "pydp",
    srcs = ["__init__.py"],
    data = ["//src/bindings:_pydp.so"],
    main = "__init__.py",
    deps = ["//src/pydp:_pydp_algo"],
)

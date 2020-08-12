load("@rules_python//python:defs.bzl", "py_binary")

py_binary(
    name = "bindings_test",
    srcs = ["__init__.py"],
    main = "__init__.py",
    data = ["//src/bindings:_pydp.so"]
)

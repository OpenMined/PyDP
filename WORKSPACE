workspace(name = "PyDP")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "pybind11_bazel",
    strip_prefix = "pybind11_bazel-26973c0ff320cb4b39e45bc3e4297b82bc3a6c09",
    urls = ["https://github.com/pybind/pybind11_bazel/archive/26973c0ff320cb4b39e45bc3e4297b82bc3a6c09.zip"],
)

# We still require the pybind library.
http_archive(
    name = "pybind11",
    build_file = "@pybind11_bazel//:pybind11.BUILD",
    strip_prefix = "pybind11-2.11.1",
    urls = ["https://github.com/pybind/pybind11/archive/v2.11.1.zip"],
)

load("@pybind11_bazel//:python_configure.bzl", "python_configure")

python_configure(name = "local_config_python")

# bazel rules for python
http_archive(
    name = "rules_python",
    sha256 = "778197e26c5fbeb07ac2a2c5ae405b30f6cb7ad1f5510ea6fdac03bded96cc6f",
    url = "https://github.com/bazelbuild/rules_python/releases/download/0.2.0/rules_python-0.2.0.tar.gz",
)

http_archive(
    name = "com_google_protobuf",
    sha256 = "7892a35d979304a404400a101c46ce90e85ec9e2a766a86041bb361f626247f5",
    strip_prefix = "protobuf-3.16.0",
    urls = [
        "https://github.com/protocolbuffers/protobuf/archive/refs/tags/v3.16.0.tar.gz",
    ],
)

http_archive(
    name = "zlib",
    build_file = "@com_google_protobuf//:third_party/zlib.BUILD",
    sha256 = "c3e5e9fdd5004dcb542feda5ee4f0ff0744628baf8ed2dd5d66f8ca1197cb1a1",
    strip_prefix = "zlib-1.2.11",
    urls = [
        "https://mirror.bazel.build/zlib.net/zlib-1.2.11.tar.gz",
        "https://zlib.net/zlib-1.2.11.tar.gz",
    ],
)

# Google DP library and it's dependencies
local_repository(
    name = "com_google_differential_privacy",
    path = "third_party/differential-privacy",
)

load("@com_google_differential_privacy//:differential_privacy_deps.bzl", "differential_privacy_deps")

differential_privacy_deps()


# Google DP library and it's dependencies
local_repository(
    name = "com_google_cc_differential_privacy",
    path = "third_party/differential-privacy/cc",
)

load("@com_google_cc_differential_privacy//:cc_differential_privacy_deps.bzl", "cc_differential_privacy_deps")

cc_differential_privacy_deps()


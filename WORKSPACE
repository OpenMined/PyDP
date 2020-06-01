workspace(name = "PyDP")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# pybind11_bazel since we need bazel rules for building pybind11.
git_repository(
    name = "pybind11_bazel",
    commit = "16ed1b8f308d2b3dec9d7e6decaad49ce4d28b43",
    remote = "https://github.com/pybind/pybind11_bazel",
)

# We still require the pybind library.
http_archive(
  name = "pybind11",
  build_file = "@pybind11_bazel//:pybind11.BUILD",
  strip_prefix = "pybind11-2.5.0",
  urls = ["https://github.com/pybind/pybind11/archive/v2.5.0.zip"],
)
load("@pybind11_bazel//:python_configure.bzl", "python_configure")
python_configure(name = "local_config_python")

# bazel rules for python
http_archive(
    name = "rules_python",
    url = "https://github.com/bazelbuild/rules_python/releases/download/0.0.2/rules_python-0.0.2.tar.gz",
    strip_prefix = "rules_python-0.0.2", 
    sha256 = "b5668cde8bb6e3515057ef465a35ad712214962f0b3a314e551204266c7be90c",
)
load("@rules_python//python:repositories.bzl", "py_repositories")
py_repositories()

# Google DP library and it's dependencies
local_repository(
    name = "google_dp",
    path = "third_party/differential-privacy",
)
load("@google_dp//:differential_privacy_deps.bzl", "differential_privacy_deps")
differential_privacy_deps()

# we still need to load Protobuf
load(
    "@com_google_protobuf//:protobuf_deps.bzl",
    "protobuf_deps",
)
protobuf_deps()

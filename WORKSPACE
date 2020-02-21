workspace(name = "PyDP")

# Creates a repository rule for the system python headers.
# pybind11.BUILD depends on this repository rule to detect your python configuration
load("//third_party/pybind11_bazel:python_configure.bzl", "python_configure")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")

python_configure(name = "local_config_python")

# Create pybind11 external repository
# If using another pybind11 version:
# Use tar URL of desired version, change strip_prefix to your version "pybind11-x.x.x",
# Supply correct sha256 for your version.
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "pybind11",
    build_file = "@//third_party/pybind11_bazel:pybind11.BUILD",
    sha256 = "1eed57bc6863190e35637290f97a20c81cfe4d9090ac0a24f3bbf08f265eb71d",
    strip_prefix = "pybind11-2.4.3",
    url = "https://github.com/pybind/pybind11/archive/v2.4.3.tar.gz",
)

# @rules_python repository, used to create python build targets
http_archive(
    name = "rules_python",
    sha256 = "aa96a691d3a8177f3215b14b0edc9641787abaaa30363a080165d06ab65e1161",
    url = "https://github.com/bazelbuild/rules_python/releases/download/0.0.1/rules_python-0.0.1.tar.gz",
)

# Currently does nothing, futureproofs your core Python rule dependencies.
load("@rules_python//python:repositories.bzl", "py_repositories")

py_repositories()

# Pulls in dependencies needed to use the python packaging rules.
load("@rules_python//python:pip.bzl", "pip_repositories")

pip_repositories()

local_repository(
    name = "google_dp",
    path = "third_party/differential-privacy",
)

git_repository(
    name = "com_google_absl",
    commit = "aae8143cf9aa611f70d7ea9b95b8b8b383b2271a",
    remote = "https://github.com/abseil/abseil-cpp",
)

# needed for protobuf
http_archive(
    name = "zlib",
    build_file = "//third_party:zlib.BUILD",
    sha256 = "c3e5e9fdd5004dcb542feda5ee4f0ff0744628baf8ed2dd5d66f8ca1197cb1a1",
    strip_prefix = "zlib-1.2.11",
    urls = [
        "http://mirror.bazel.build/zlib.net/fossils/zlib-1.2.11.tar.gz",
        "http://zlib.net/fossils/zlib-1.2.11.tar.gz",  # 2017-01-15
    ],
)

http_archive(
            name = "bazel_skylib",
            type = "tar.gz",
            url = "https://github.com/bazelbuild/bazel-skylib/releases/download/0.8.0/bazel-skylib.0.8.0.tar.gz",
            sha256 = "2ef429f5d7ce7111263289644d233707dba35e39696377ebab8b0bc701f7818e",
        )

http_archive(
            name = "com_google_protobuf",
            urls = ["https://github.com/protocolbuffers/protobuf/archive/v3.8.0.tar.gz"],
            sha256 = "03d2e5ef101aee4c2f6ddcf145d2a04926b9c19e7086944df3842b1b8502b783",
            strip_prefix = "protobuf-3.8.0",
        )


http_archive(
    name = "boringssl",
    build_file = "//third_party:boringssl.BUILD",
    urls = [
        "https://boringssl.googlesource.com/boringssl/+archive/master-with-bazel.tar.gz"
    ],
)
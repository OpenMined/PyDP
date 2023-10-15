#!/bin/bash
# This script differs from build_PyDP.sh by installing bazel first (if needed).
BAZELISK_VERSION=v1.8.1
BAZELISK_BINARY=bazelisk-linux-amd64
BAZELISK_DOWNLOAD_URL=https://github.com/bazelbuild/bazelisk/releases/download/

if command -v bazel &>/dev/null; then
    echo "Bazel already installed"
else
  python -m wget "${BAZELISK_DOWNLOAD_URL}/${BAZELISK_VERSION}/${BAZELISK_BINARY}"
  chmod +x ${BAZELISK_BINARY}
  mkdir bazel_dir
  echo mv ${BAZELISK_BINARY} bazel_dir/bazel
  mv ${BAZELISK_BINARY} bazel_dir/bazel
  export PATH="$PATH:`pwd`/bazel_dir"
fi

./build_PyDP.sh

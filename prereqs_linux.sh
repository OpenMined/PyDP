#!/bin/bash

BAZELISK_VERSION=v1.8.1
BAZELISK_BINARY=bazelisk-linux-amd64
BAZELISK_DOWNLOAD_URL=https://github.com/bazelbuild/bazelisk/releases/download/

# checking for g++
dpkg -s g++ &> /dev/null
if [ $? -eq 0 ]; then
    echo "g++ is installed, skipping..."
else
    echo "Installing g++"
    sudo apt-get install g++
fi

# checking for python 3.6
echo "Checking for python3 installation"
if command -v python3 &>/dev/null; then
    echo "Python 3 already installed"
    elif command python --version | grep -q 'Python 3'; then
    echo "Python 3 already installed"
else
    echo "Installing Python 3 is not installed"  
    sudo add-apt-repository ppa:deadsnakes/ppa
    sudo apt-get update
    sudo apt-get install python3.6
fi

# checking for poetry
echo "Checking for poetry"
if python3 -c "import poetry" &> /dev/null; then
    echo "poetry is already installed"
else
    echo "Installing poetry"
    pip3 install poetry
fi

# bazel
if command -v bazel &>/dev/null; then
    echo "Bazel already installed"
else
    echo "Installing Bazel dependencies"
    sudo apt-get install pkg-config zip zlib1g-dev unzip
    wget "${BAZELISK_DOWNLOAD_URL}/${BAZELISK_VERSION}/${BAZELISK_BINARY}" && \
    chmod +x ${BAZELISK_BINARY}
    mv ${BAZELISK_BINARY} $HOME/bin/bazel
    export PATH="$PATH:$HOME/bin"
fi

# clang-format
if command -v clang-format &>/dev/null; then
    echo "clang-format already installed"
else
    echo "installing clang-format"
    sudo apt-get install clang-format
fi

# Downloading the Google DP library
git submodule update --init --recursive


# checkout out to particular commit
cd third_party/differential-privacy && git checkout e224a8635728026fb3aa9409ab3a98b9a3f5566a && \
cd -
# renaming workspace.bazel to workspace
mv third_party/differential-privacy/cc/WORKSPACE.bazel third_party/differential-privacy/cc/WORKSPACE

# Removing the java part
rm -rf third_party/differential-privacy/java third_party/differential-privacy/examples/java

# Removing the Go part
rm -rf third_party/differential-privacy/go third_party/differential-privacy/examples/go

# Removing the Privacy on Beam  
rm -rf third_party/differential-privacy/privacy-on-beam
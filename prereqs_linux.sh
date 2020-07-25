#!/bin/bash

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

# checking for pipenv
echo "Checking for pipenv"
if python3 -c "import pipenv" &> /dev/null; then
    echo "pipenv is already installed"
else
    echo "Installing pipenv"
    pip3 install pipenv
fi

# bazel
if command -v bazel &>/dev/null; then
    echo "Bazel already installed"
else
    echo "Installing Bazel dependencies"
    sudo apt-get install pkg-config zip zlib1g-dev unzip
    echo "Donwloading Bazel 2.1.0"
    wget https://github.com/bazelbuild/bazel/releases/download/2.1.0/bazel-2.1.0-installer-linux-x86_64.sh

    chmod +x bazel-2.1.0-installer-linux-x86_64.sh
    ./bazel-2.1.0-installer-linux-x86_64.sh --user
    export PATH="$PATH:$HOME/bin"
    rm bazel-2.1.0-installer-linux-x86_64.sh
fi


# Downloading the Google DP library
git submodule update --init --recursive

# checkout out to particular commit
cd third_party/differential-privacy && git checkout d9f9215deec7f6bc85b1076a220dc83795cb0be8 && \
cd -
# renaming workspace.bazel to workspace
mv third_party/differential-privacy/cc/WORKSPACE.bazel third_party/differential-privacy/cc/WORKSPACE

# Removing the java part
rm -rf third_party/differential-privacy/java third_party/differential-privacy/examples/java

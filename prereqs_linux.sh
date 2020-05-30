#!/bin/bash

# checking for g++
dpkg -s g++ &> /dev/null
if [ $? -eq 0 ]; then
    echo "g++ is installed, skipping..."
else
    echo "Installing g++"
    sudo apt-get install g++
fi

# python 3.6
echo "Checking for python3 installation"
if command -v python3 &>/dev/null; then
    echo "Python 3 already installed"
else
    echo "Installing Python 3 is not installed"
    sudo add-apt-repository ppa:deadsnakes/ppa
    sudo apt-get update
    sudo apt-get install python3.6
fi

# pipenv
echo "Checking for pipenv"
dpkg -s pipenv &> /dev/null
if command [ $? -eq 0 ]; then
    echo "pipenv is already installed"
else
    echo "installing pipenv"
    sudo apt install pipenv
fi

# checking for bazel
echo "Installing Bazel dependencies"
sudo apt-get install pkg-config zip zlib1g-dev unzip
echo "Donwloading Bazel 2.1.0"
wget https://github.com/bazelbuild/bazel/releases/download/2.1.0/bazel-2.1.0-installer-linux-x86_64.sh

chmod +x bazel-2.1.0-installer-linux-x86_64.sh
./bazel-2.1.0-installer-linux-x86_64.sh --user
export PATH="$PATH:$HOME/bin"
rm bazel-2.1.0-installer-linux-x86_64.sh


# Downloading the Google DP library
git submodule update --init --recursive
# Removing the Java part 
rm -rf third_party/differential-privacy/java 
rm -rf third_party/differential-privacy/examples/java
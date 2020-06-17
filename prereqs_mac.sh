#!/bin/bash

# homebrew
which -s brew
if [[ $? != 0 ]] ; then
    # Install Homebrew
    echo "Downloading and installing homebrew"
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"
else
    brew update
fi

# python 3
echo "Checking for python3 installation"
if command -v python3 &>/dev/null; then
    echo "Python 3 already installed"
else
    echo "Downloading and installing Python3 using homebrew"
    brew install python3
fi

# bazel
if command -v bazel &>/dev/null; then
    echo "Bazel already installed"
else
    echo "Downloading and installing Bazel using homebrew"
    brew tap bazelbuild/tap
    brew install bazelbuild/tap/bazel
fi

# pipenv
echo "Checking for pipenv"
if python3 -c "import pipenv" &> /dev/null; then
    echo "pipenv is already installed"
else
    echo "installing pipenv"
    pip3 install pipenv
fi

# Downloading the Google DP library
git submodule update --init --recursive

# checkout out to particular commit
cd third_party/differential-privacy && git checkout b7f4c39d9f73d67b34cdbd1b8483e5f72072fc73

cd -
# renaming workspace.bazel to workspace
mv third_party/differential-privacy/cc/WORKSPACE.bazel third_party/differential-privacy/cc/WORKSPACE

# Removing the Java part 
rm -rf third_party/differential-privacy/java third_party/differential-privacy/examples/java

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

# clang-format
if command -v clang-format &>/dev/null; then
    echo "clang-format already installed"
else
    echo "installing clang-format"
    brew install clang-format
fi

# pipenv
echo "Checking for pipenv"
if python3 -c "import pipenv" &> /dev/null; then
    echo "pipenv is already installed"
else
    echo "installing pipenv"
    pip3 install pipenv
fi

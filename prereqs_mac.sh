#!/bin/bash

which -s brew
if [[ $? != 0 ]] ; then
    # Install Homebrew
    echo "Donwloading and installing homebrew"
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"
else
    brew update
fi

# TODO Python checking and installation

# checking for bazel
echo "Donwloading and installing Bazel using homebrew"
brew tap bazelbuild/tap
brew install bazelbuild/tap/bazel

echo "Donwloading and installing gnu-sed using homebrew"
brew install gnu-sed

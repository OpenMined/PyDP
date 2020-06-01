#!/bin/bash

which -s brew
if [[ $? != 0 ]] ; then
    # Install Homebrew
    echo "Downloading and installing homebrew"
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"
else
    brew update
fi

# TODO: We want to check if user has python already installed.
# In-case if they have some other version of python installed, 
# this will create yet another installation.

# echo "Downloading and installing Python3 using homebrew"
# brew install python3

# checking for bazel
echo "Downloading and installing Bazel using homebrew"
brew tap bazelbuild/tap
brew install bazelbuild/tap/bazel


# Downloading the Google DP library
git submodule update --init --recursive
# Removing the Java part 
rm -rf third_party/differential-privacy/java 
rm -rf third_party/differential-privacy/examples/java
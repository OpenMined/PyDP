#!/bin/bash

which -s brew
if [[ $? != 0 ]] ; then
    # Install Homebrew
    echo "Downloading and installing homebrew"
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"
else
    brew update
fi

echo "Downloading and installing Python3 using homebrew"
brew install python3

# checking for bazel
echo "Downloading and installing Bazel using homebrew"
brew tap bazelbuild/tap
brew install bazelbuild/tap/bazel

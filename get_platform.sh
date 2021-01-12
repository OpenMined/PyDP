#!/bin/bash

## Set variables

# Get platform value for bazel
# Bazel expects as config values: linux, arm, osx, windows, etc
PLATFORM=$RUNNER_OS

if [ -z "$PLATFORM" ]; then
    PLATFORM=$OSTYPE
fi

# Make value lowercase
PLATFORM=$(echo "$PLATFORM" | tr '[:upper:]' '[:lower:]')

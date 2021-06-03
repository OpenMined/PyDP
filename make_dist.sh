#!/bin/bash

PLATFORM=$(python scripts/get_platform.py)
BUILD_ARGS=""
if [ $PLATFORM == "macos" ]; then
    BUILD_ARGS="--plat-name macosx_10_14_x86_64"
fi
echo $BUILD_ARGS
poetry run python setup.py bdist_wheel $BUILD_ARGS
ls -l dist

#!/bin/bash

## Set variables
source ./get_platform.sh

poetry run python setup.py sdist
case $PLATFORM in
  *"linux"*)
    poetry run python setup.py bdist_wheel
    ;;
  *"macos"* | *"darwin"*)
    poetry run python setup.py bdist_wheel --plat-name macosx_10_15_x86_64
    ;;
esac
ls -l dist

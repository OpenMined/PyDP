#!/bin/bash

pipenv install --dev --skip-lock
bazel build src/python:bindings_test  --verbose_failures
find ./ -name _pydp.so -print0 | xargs -0 -I {} rm {}
cp -f ./bazel-bin/src/bindings/_pydp.so ./pydp

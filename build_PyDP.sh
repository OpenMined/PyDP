#!/bin/bash

poetry install
bazel coverage src/python:bindings_test --config Linux src/python:bindings_test  --verbose_failures
find ./ -name _pydp.so -print0 | xargs -0 -I {} rm -r {}
cp -f ./bazel-bin/src/bindings/_pydp.so ./pydp
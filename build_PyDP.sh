#!/bin/bash 

pipenv run pipenv install --dev --skip-lock
pipenv run bazel build src/python:bindings_test  --verbose_failures
find ./ -name pydp.so -print0 | xargs -0 -I {} rm {}
cp -f ./bazel-bin/src/bindings/pydp.so ./pydp

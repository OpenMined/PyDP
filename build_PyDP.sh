#!/bin/bash 

pipenv run pipenv install --dev --skip-lock
pipenv run bazel build src/python:bindings_test  --verbose_failures
rm -f pydp.so
cp -f ./bazel-bin/src/bindings/pydp.so ./pydp

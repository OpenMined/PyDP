#!/bin/bash
pip install --upgrade pipenv
pipenv run pipenv install --dev --skip-lock
pipenv run bazel build src/python:bindings_test  --verbose_failures
cp -f ./bazel-bin/src/bindings/pydp.so ./pydp
cp -f ./bazel-bin/src/bindings/pydp.so ./examples
pipenv run python examples/carrots.py
#!/bin/bash 
 
bazel build src/python:bindings_test --verbose_failures
rm -f PyDP.so
cp -f ./bazel-bin/src/bindings/pydp.so .
python test.py
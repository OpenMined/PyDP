#!/bin/bash 
 
bazel build src/python:bindings_test
rm -f PyDP.so
cp -f ./bazel-bin/src/bindings/PyDP.so .
# python test.py
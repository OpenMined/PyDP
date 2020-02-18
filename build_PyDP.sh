#!/bin/bash 
 
bazel build src/python:bindings_test
cp ./bazel-bin/src/bindings/PyDP.so .
python test.py
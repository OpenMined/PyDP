#!/bin/bash 

PARAMS=""
while (( "$#" )); do
  case "$1" in
    -f|--first_time)
        FARG=$2
        echo "-f option passed"
        shift 2
        sed -i '159i\ \ \ \ python_bin_path=repository_ctx.which("python3")\n\ \ \ \ if\ python_bin_path != None:\n\ \ \ \ \ \ \ \ return\ str(python_bin_path)' ./third_party/pybind11_bazel/python_configure.bzl
        sed -i '18s/py/third_party\/pybind11_bazel\/py/' ./third_party/pybind11_bazel/python_configure.bzl
        sed -i '12iPYBIND11_BAZEL_DIR = "//third_party/pybind11_bazel"' ./third_party/pybind11_bazel/python_configure.bzl
        break
        ;; 
    --) # end argument parsing
      shift
      break
      ;;
    -*|--*=) # unsupported flags
      echo "Error: Unsupported flag $1" >&2
      exit 1
      ;;
    *) # preserve positional arguments
      PARAMS="$PARAMS $1"
      shift
      ;;
  esac
done

eval set -- "$PARAMS"


bazel build src/python:bindings_test  --verbose_failures
rm -f pydp.so
cp -f ./bazel-bin/src/bindings/pydp.so .

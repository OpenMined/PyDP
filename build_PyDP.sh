#!/bin/bash 

EDITION_MARK='# edited by PyDP build script'
PYTHON_CONFIGURE_BZL_PATH='./third_party/pybind11_bazel/python_configure.bzl'

if ! grep -Fxq "$EDITION_MARK" $PYTHON_CONFIGURE_BZL_PATH
then
    gsed -i '159i\ \ \ \ python_bin_path=repository_ctx.which("python3")\n\ \ \ \ if\ python_bin_path != None:\n\ \ \ \ \ \ \ \ return\ str(python_bin_path)' $PYTHON_CONFIGURE_BZL_PATH
    gsed -i '18s/py/third_party\/pybind11_bazel\/py/' $PYTHON_CONFIGURE_BZL_PATH
    gsed -i '12iPYBIND11_BAZEL_DIR = "//third_party/pybind11_bazel"' $PYTHON_CONFIGURE_BZL_PATH
    gsed -i "8i$EDITION_MARK" $PYTHON_CONFIGURE_BZL_PATH
fi

PARAMS=""
while (( "$#" )); do
  case "$1" in
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
cp -f ./bazel-bin/src/bindings/pydp.so ./pydp
cp -f ./bazel-bin/src/bindings/pydp.so ./examples

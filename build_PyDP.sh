#!/bin/bash

###################################################################
# Link to repository fetched with bazel git_repository
rm -f third_party/differential-privacy
ln -s $(bazel info output_base)/external/com_google_differential_privacy third_party/differential-privacy
###################################################################

pipenv install --dev --skip-lock
bazel coverage src/python:bindings_test --verbose_failures
find ./ -name _pydp.so -print0 | xargs -0 -I {} rm {}
cp -f ./bazel-bin/src/bindings/_pydp.so ./pydp

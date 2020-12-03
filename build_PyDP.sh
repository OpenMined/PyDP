#!/bin/bash

# Setup poetry env
poetry install

# Search specific python bin and lib folders to compile against the poetry env
PYTHONHOME=$(poetry run which python)
PYTHONPATH=$(poetry run python -c 'import sys; print([x for x in sys.path if "site-packages" in x][0]);')

bazel coverage src/python:bindings_test \
  --config Linux src/python:bindings_test \
  --verbose_failures \
  --action_env=PYTHON_BIN_PATH=$PYTHONHOME \
  --action_env=PYTHON_LIB_PATH=$PYTHONPATH

# Delete the previously compiled package and copy the new one
find ./ -name _pydp.so -print0 | xargs -0 -I {} rm -r {}
cp -f ./bazel-bin/src/bindings/_pydp.so ./src/pydp

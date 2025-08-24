#!/bin/bash
set -e # exit on error

echo "*** Build start"
pwd
ls -l

mkdir -p build
cd build 
pwd
cmake .. -DCMAKE_BUILD_TYPE=Release
make _pydp -j 
mv ./src/bindings/PyDP/_pydp*so ../src/pydp/_pydp.so 

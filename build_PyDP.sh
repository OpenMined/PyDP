#!/bin/bash
set -e # exit on error

mkdir -p build
cd build 
cmake .. -DCMAKE_BUILD_TYPE=Release
make _pydp -j 
mv ./src/bindings/PyDP/_pydp*so ../src/pydp/_pydp.so 

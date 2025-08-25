#!/bin/bash
set -e # exit on error

mkdir -p build
cd build 
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES=arm64
make _pydp -j 
mv ./src/bindings/PyDP/_pydp*so ../src/pydp/_pydp.so 

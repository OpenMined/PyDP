#!/bin/bash

echo "*** Installing libssl"
sudo apt install libssl-dev
echo "**** Finished libssl install"
./build_PyDP.sh

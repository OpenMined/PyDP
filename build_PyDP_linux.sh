#!/bin/bash

echo "*** Installing libssl"
apt-get install libssl-dev
echo "**** Finished libssl install"
./build_PyDP.sh

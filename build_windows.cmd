mkdir build_dir
cd build_dir
cmake -S .. -B .  -DOPENSSL_ROOT_DIR="C:\Program Files\OpenSSL"
cmake --build . --parallel --config Release
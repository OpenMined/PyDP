mkdir build_dir
cd build_dir
cmake -S .. -B .  -DOPENSSL_ROOT_DIR="C:\Program Files\OpenSSL" -DOPENSSL_USE_STATIC_LIBS=TRUE
cmake --build . --parallel --config Release
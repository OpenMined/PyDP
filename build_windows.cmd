@REM git clone https://github.com/Delphier/dumpbin.git
@REM echo Y| python dumpbin/dumpbin.py
@REM dumpbin.exe /exports *.dll

mkdir build_dir
cd build_dir
cmake -S .. -B . -DOPENSSL_ROOT_DIR="C:\Program Files\OpenSSL"
cmake --build . --parallel --config Release

move "src\bindings\PyDP\Release\_pydp.*-win_amd64.pyd" "..\src\pydp\"
cd ..\src\pydp\
ren "_pydp.*-win_amd64.pyd" "_pydp.pyd"
dir "C:\Program Files\OpenSSL"
dir "C:\Program Files\OpenSSL\bin"
copy "C:\Program Files\OpenSSL\libcrypto*.dll" .
dumpbin.exe /dependents "_pydp.pyd"
dumpbin.exe /dependents "libcrypto-3-x64.dll"

python -c "import _pydp"
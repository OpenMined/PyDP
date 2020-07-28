
# windows build notes:
## Issues
There seem to be a few minor issues causing the windows build to fail. 
1. `copts = ["-Wno-sign-compare"],` flag in `third_party\differential-privacy\cc\*\BUILD` files. 
The HACK solution was to do a find replace to remove them. The better solution would be to use the `nocopts -` but my attempts probably failed due to user error.
2. `third_party\differential-privacy\cc\base\logging.cc` makes use of `unistd.h`. I have put a rudementry fix in `src\patched_logging.cc` but ideally the upstream team will do better when they offically support windows.
3. The c_api.cc ad c_api.h do not build on windows with either "cl.exe" or "clang-cl.exe". The following functions: `Result_Percentile`, `Result_Median`, `Result_Min`, `Result_Max`
*Any comments on this would be of assistance.*
cause errors:

```
C:\Program Files (x86)\Windows Kits\10\include\10.0.18362.0\ucrt\corecrt_math.h(415): error C2668: 'fpclassify': ambiguous call to overloaded function   
C:\Program Files (x86)\Windows Kits\10\include\10.0.18362.0\ucrt\corecrt_math.h(300): note: could be 'int fpclassify(long double) throw()'
C:\Program Files (x86)\Windows Kits\10\include\10.0.18362.0\ucrt\corecrt_math.h(295): note: or       'int fpclassify(double) throw()'
C:\Program Files (x86)\Windows Kits\10\include\10.0.18362.0\ucrt\corecrt_math.h(290): note: or       'int fpclassify(float) throw()'
C:\Program Files (x86)\Windows Kits\10\include\10.0.18362.0\ucrt\corecrt_math.h(415): note: while trying to match the argument list '(_Ty)'
        with
        [
            _Ty=int64_t
        ]
C:\users\benja\_bazel_benja\qsn7v6mh\execroot\PyDP\external\google_dp\algorithms/binary-search.h(84): note: see reference to function template instantiation 'bool isnan<T>(_Ty) throw()' being compiled
        with
        [
            T=int64_t,
            _Ty=int64_t
        ]
C:\users\benja\_bazel_benja\qsn7v6mh\execroot\PyDP\external\google_dp\algorithms/binary-search.h(83): note: while compiling class template member function 'void differential_privacy::BinarySearch<T>::AddEntry(const T &)'
        with
        [
            T=int64_t
        ]
src/bindings/c/c_api.cc(170): note: see reference to function template instantiation 'void differential_privacy::BinarySearch<T>::AddEntry(const T &)' being compiled
        with
        [
            T=int64_t
        ]
C:\users\benja\_bazel_benja\qsn7v6mh\execroot\PyDP\external\google_dp\algorithms/order-statistics.h(80): note: see reference to class template instantiation 'differential_privacy::BinarySearch<T>' being compiled
        with
        [
            T=int64_t
        ]
src/bindings/c/c_api.cc(158): note: see reference to class template instantiation 'differential_privacy::continuous::Max<int64_t>' being compiled        
Target //src/python:bindings_win failed to build
INFO: Elapsed time: 2.348s, Critical Path: 2.09s
INFO: 0 processes.
FAILED: Build did NOT complete successfully

```


## Gotchas and todos
- Python will not load a .dll file it needs to be a .pyd file. These are identical baring the extention and so renaming is fine(ish).
- Be sure to set these two otherwise the produced .dll might link to another version of python (see todo below).
`set PYTHON_LIB_PATH="C:\\Users\\benja\\Documents\\openmined\\PyDP_new\\PyDP\\.venv\\Lib"`
`set PYTHON_BIN_PATH="C:\\Users\\benja\\Documents\\openmined\\PyDP_new\\PyDP\\.venv\\Scripts\\python.exe"`

### todo:
convention is to generate `{package_name}.cp38-win_amd64.pyd` for a python 3.8 windows file. add bazel configs to build such files.

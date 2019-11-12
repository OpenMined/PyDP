from distutils.core import setup, Extension

absl_module  = Extension('_absl',
    sources = ['absl_wrap.cxx', "differential_privacy/base/status.cc"],
    include_dirs=['./', 'third_party/abseil-cpp', './differential-privacy']
)

setup ( name= 'PyDP',
        version = "0.1",
        author = "OpenMined",
        description = "Python container for Google DP library",
        ext_modules = [absl_module],
        py_modules = ["absl"],
)
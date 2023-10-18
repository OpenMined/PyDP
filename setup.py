#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""The setup script."""
import os
import platform
import sys
from typing import List

from setuptools import find_packages
from setuptools import setup
from setuptools.dist import Distribution
from setuptools.command.build_ext import build_ext

CONDA_PREFIX = os.environ.get("CONDA_PREFIX", None)
WORKING_DIR = os.getcwd()


class Build(build_ext):
    """Customized setuptools build command - builds protos on build."""

    def run(self):
        if platform.system() != "Linux":
            # For Windows and Mac setup.py is not used for wheel build but the
            # build is performed from GitHub actions files. The special
            # treatment for Linux is required because wheel build is performed
            # inside manylinux Docker images with the help of cibuildwheel
            # (https://github.com/pypa/cibuildwheel). Building with manylinux
            # ensures that PyDP can work on old Linux versions.
            return

        # Build _pydp.so (wrappers for C++).
        os.system("./build_PyDP_linux.sh")

        # Copy _pydp.so to cibuildwheel directory.
        pydp_lib = "src/pydp/_pydp.so"
        version_str = f"{sys.version_info.major}{sys.version_info.minor}"
        destination_dir = f"build/lib.linux-x86_64-cpython-{version_str}/pydp"
        os.system(f"cp {pydp_lib} {destination_dir}")

        build_ext.run(self)


class BinaryDistribution(Distribution):
    """This class is needed in order to create OS specific wheels."""

    def has_ext_modules(self):
        return True


def read(fname):
    with open(os.path.join(os.path.dirname(__file__), fname), encoding="utf-8") as fp:
        return fp.read()


requirements: List[str] = []
setup_requirements: List[str] = []


setup(
    author="Chinmay Shah",
    author_email="chinmayshah3899@gmail.com",
    classifiers=[
        "Development Status :: 5 - Production/Stable",
        "Intended Audience :: Developers",
        "Natural Language :: English",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.8",
        "Programming Language :: Python :: 3.9",
        "Programming Language :: Python :: 3.10",
        "Programming Language :: Python :: 3.11",
    ],
    cmdclass={"build_ext": Build},
    description="Python API for Google's Differential Privacy library",
    distclass=BinaryDistribution,
    install_requires=requirements,
    license="Apache-2.0",
    long_description=read("docs/readme.rst"),
    long_description_content_type="text/x-rst",
    include_package_data=True,
    keywords="pydp",
    name="python-dp",
    package_dir={"": "src"},
    package_data={
        "pydp": ["_pydp.so", "_pydp.pyd"],
    },
    packages=find_packages(where="src", exclude=["tests"]),
    setup_requires=setup_requirements,
    python_requires=">=3.8",
    test_suite="tests",
    url="https://github.com/OpenMined/PyDP",
    version="1.1.5.rc2",
    zip_safe=False,
)

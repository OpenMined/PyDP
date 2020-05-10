#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""The setup script."""

from setuptools import setup, find_packages
from setuptools.dist import Distribution
from setuptools.command.install import install

import os


class InstallPlatlib(install):
    def finalize_options(self):
        install.finalize_options(self)
        if self.distribution.has_ext_modules():
            self.install_lib = self.install_platlib


class BinaryDistribution(Distribution):
    """This class is needed in order to create OS specific wheels."""

    def has_ext_modules(self):
        return True


def read(fname):
    return open(os.path.join(os.path.dirname(__file__), fname)).read()


requirements = []

setup_requirements = []

test_requirements = []

setup(
    author="Chinmay Shah",
    author_email="chinmayshah3899@gmail.com",
    classifiers=[
        "Development Status :: 2 - Pre-Alpha",
        "Intended Audience :: Developers",
        "Natural Language :: English",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.5",
        "Programming Language :: Python :: 3.6",
        "Programming Language :: Python :: 3.7",
    ],
    description="Python API for Google's Differential Privacy library",
    distclass=BinaryDistribution,
    install_requires=requirements,
    license="Apache-2.0",
    long_description=read("docs/readme.rst"),
    include_package_data=True,
    keywords="pydp",
    name="python-dp",
    package_data={"pydp": ["pydp.so"],},
    packages=find_packages(exclude=["tests/"]),  # need to check this
    cmdclass={"install": InstallPlatlib},
    setup_requires=setup_requirements,
    test_suite="tests",
    tests_require=test_requirements,
    url="https://github.com/OpenMined/PyDP",
    version="0.1.1",
    zip_safe=False,
)

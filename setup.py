#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""The setup script."""

from setuptools import setup, find_packages
from setuptools.dist import Distribution
from setuptools.command.install import install

import os


class BinaryDistribution(Distribution):
    """This class is needed in order to create OS specific wheels."""

    def has_ext_modules(self):
        return True


def read(fname):
    with open(os.path.join(os.path.dirname(__file__), fname), encoding="utf-8") as fp:
        return fp.read()


requirements = []

setup_requirements = []


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
        "Programming Language :: Python :: 3.8",
    ],
    description="Python API for Google's Differential Privacy library",
    distclass=BinaryDistribution,
    install_requires=requirements,
    license="Apache-2.0",
    long_description=read("docs/readme.rst"),
    long_description_content_type="text/x-rst",
    include_package_data=True,
    keywords="pydp",
    name="python-dp",
    package_data={"pydp": ["_pydp.so", "_pydp.pyd"],},
    packages=find_packages(exclude=["tests"]),  # need to check this
    setup_requires=setup_requirements,
    test_suite="tests",
    url="https://github.com/OpenMined/PyDP",
    version="1.0.1",
    zip_safe=False,
)

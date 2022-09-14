#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""The setup script."""

# stdlib
import os
from typing import List

# third party
from setuptools import find_packages
from setuptools import setup
from setuptools.dist import Distribution


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
        "Programming Language :: Python :: 3.7",
        "Programming Language :: Python :: 3.8",
        "Programming Language :: Python :: 3.9",
        "Programming Language :: Python :: 3.10",
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
    package_dir={"": "src"},
    package_data={
        "pydp": ["_pydp.so", "_pydp.pyd"],
    },
    packages=find_packages(where="src", exclude=["tests"]),
    setup_requires=setup_requirements,
    python_requires=">=3.7",
    test_suite="tests",
    url="https://github.com/OpenMined/PyDP",
    version="1.1.2rc2",
    zip_safe=False,
)

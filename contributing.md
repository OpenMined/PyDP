# Contributors Guidelines to PyDP

## About PyDP

The project uses [Pybind11](http://pybind11.readthedocs.io) to wrap Google's [Differential Privacy](https://github.com/google/differential-privacy) library.

The library is written in C++, so it is best you have some familiarity with that language before attempting to help out here.

You can check out [here](https://www.learncpp.com/) to get your started about C++.

Regarding Pybind, Here is a good [introduction](https://www.youtube.com/watch?v=jQedHfF1Jfw) about it.

## Setting up your Environment

Three scripts are available to help get your environment ready set up.

### Git Submodules

Currently we are using git submodules to allow editors like VSCode to locate source code, this should be refactored later.

This clones Google's differential privacy library as well as some other third party dependencies.

```
$ ./ext_source_setup.sh
```

or simply type:

```
$ git submodule update --init --recursive
```

### Install Script

This script automates the installation of the prerequisite packages to get you started, you can optionally install these manually referring to the list below.

```
$ ./prereqs.sh
```

### Build Script

Build the python library:

```
$ ./build_PyDP.sh
```

Build the python wheel:

```
$ python3 setup.py sdist bdist_wheel
```

Install wheel:

```
$ pip install dist/pydp-0.1.0-py2.py3-none-any.whl
```

### Docker Support

Dockerfile is added so users on all systems can get involved in development. Windows developers can start contrbiuting with the help of Docker support.

To build the image:

```
$ docker build -t pydp:test
```

To run the image:

```
$ docker run --rm -it pydp:test
```

Docker Run will allow to interactively with the files; to check if your code works perfectly, you can type:

```
$ make test-all
```

To run the code, you can open python interpretor inside the container by typing

```
$ python
```

Note: After each change in your code, you have to run:

```
$ docker build
```

## Pre-requisites

Nothing in particular, prereqs takes care of everything.

## Project Structure

_To be updated_

### Third Party dependencies

Make sure you run:

```
$ ./ext_source_setup.sh
```

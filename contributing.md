# Contributors Guidelines to PyDP

## About PyDP

The project uses [Pybind11](http://pybind11.readthedocs.io) to wrap Google's [Differential Privacy](https://github.com/google/differential-privacy) library.

The library is written in C++, so it is best you have some familiarity with that language before attempting to help out here.

You can check out [here](https://www.learncpp.com/) to get your started about C++.

Regarding Pybind, Here is a good [introduction](https://www.youtube.com/watch?v=jQedHfF1Jfw) about it.

## Setting up your Environment

### Install Script

This script automates the installation of the prerequisite packages to get you started, you can optionally install these manually referring to the list in the said file.

If you are on Linux
```
$ ./prereqs_linux.sh  
```
If you are on OSX
```
$ ./prereqs_mac.sh
```

### Build Script

To achieve clean builds of different python versions we are using a virtualenv to isolate
the build process from system python and system libraries. Since python2 is deprecated
pipenv should be looking for a python3 binary to create the virtualenv from by default.
If you want to use a specific version of python3 please refer to the
[pipenv documentation](https://pipenv-fork.readthedocs.io/en/latest/).

Build the python library:

```
$ ./build_PyDP.sh
```

Run the test example:
```
$ pipenv run python examples/carrots.py
```

Build the python wheel:

```
$ pipenv run python setup.py bdist_wheel
```

Install wheel:

```
$ pip install dist/*.whl
```

## Docker Support

Dockerfile is added so users on all systems can get involved in development.
Windows developers can start contributing with the help of Docker support.

To build the image with the default python version:

```
$ docker build -t pydp:test .
```

To change the python version use the --build-arg parameter:

```
$ docker build --build-args PYTHON_VERSION=3.8 -t pydp:test .
```

To run the image:

```
$ docker run --rm -it pydp:test
```

Docker Run will allow to interactively with the files; to check if your code works
perfectly, you can type:

```
$ make test-all
```

To run the code, you can open python interpreter inside the container by typing

```
$ python
```

Note: After each change in your code, you have to run:

```
$ docker build -t pydp:test .
```

## Coding Standards

For Naming of modules, classes and methods in Python, make sure you follow naming
conventions found
[here](https://visualgit.readthedocs.io/en/latest/pages/naming_convention.html).

For C++ Styling, we follow Google's coding standard. Read more about it
[here](./.clang-format).

For Python Formatting, we use
[Black](https://black.readthedocs.io/en/stable/the_black_code_style.html),
a stricter subset of PEP8.

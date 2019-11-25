# Contributors Guidelines to PyDP

## About PyDP

The project uses [SWIG](http://swig.org) to wrap Google's [Differential Privacy](https://github.com/google/differential-privacy) library. The library is written in C++, so it is best you have some familiarity with that language before attempting to help out here. You can check out [here](https://www.learncpp.com/) to get your started,

## Setting up your environment

Two installation scripts are available to help get your environment ready set up:
- ext_source_setup - This clones Google's differential privacy library as well as some other third party dependencies.
- prereqs - This script automates the installation of the prerequisite packages to get you started, you can optionally install these manually referring to the list below.

It is worth noting that whilst you can absolutely set up a Windows environment, it is a lot simpler to get started with Linux. For Windows 10 users, we'd highly recommend the [Windows Subsystem for Linux](https://docs.microsoft.com/en-us/windows/wsl/install-win10) and the very handly [Remote - WSL](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-wsl) extension for VS Code.

## Pre-requisites

The following are required before the project can be built:
- A C++ compiler (g++ etc...), with make (many linux distros will have set up for you by default)
- PCRE3 - a Perl 5 compatible regular expression library. This is something that SWIG makes use of
- [SWIG](http://swig.org) - The tools that lets us wrap our C++ code in a Python library. It also lets you rwap your C/C++ into all sorts of other languages like Ruby, JavaScript etc...

## Project Structure

*To be updated*

### Third Party dependencies

All the dependencies have been checkout to the their most stable version with branch name `pydp-stable`. This is made to ensure that in-case these repos update, they don't break our repo.
Please ensure that if you update these third party dependecies to there latest version, you make sure to run relevant tests.

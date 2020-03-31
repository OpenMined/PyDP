# Contributors Guidelines to PyDP

## About PyDP

The project uses [Pybind11](http://pybind11.readthedocs.io) to wrap Google's [Differential Privacy](https://github.com/google/differential-privacy) library. 
The library is written in C++, so it is best you have some familiarity with that language before attempting to help out here. 

You can check out [here](https://www.learncpp.com/) to get your started about C++.

Regarding Pybind, Here is a good [introduction](https://www.youtube.com/watch?v=jQedHfF1Jfw) about it.

## Setting up your environment

Two installation scripts are available to help get your environment ready set up:
- ext_source_setup - This clones Google's differential privacy library as well as some other third party dependencies.
- prereqs - This script automates the installation of the prerequisite packages to get you started, you can optionally install these manually referring to the list below.
- Run the command: ```build_PyDP.sh -f```

It is worth noting that whilst you can absolutely set up a Windows environment, it is a lot simpler to get started with Linux. For Windows 10 users, we'd highly recommend the [Windows Subsystem for Linux](https://docs.microsoft.com/en-us/windows/wsl/install-win10) and the very handly [Remote - WSL](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-wsl) extension for VS Code.


Build python wheel: ```python3 setup.py sdist bdist_wheel```

Install wheel: ```pip install dist/pydp-0.1.0-py2.py3-none-any.whl```

## Pre-requisites

Nothing in particular, prereqs takes care of everything.

## Project Structure

*To be updated*

### Third Party dependencies

Make sure you run ext_source_setup.

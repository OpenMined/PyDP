# Contributors Guidelines to PyDP

## Getting Started

### Learn Git and Github

All our development is done using Git and Github. If you're not too familiar with Git and Github, start by reviewing this guide. <https://guides.github.com/activities/hello-world/>

### Slack

A great first place to join the Community is the Slack workspace <http://slack.openmined.org>.
- For support in using this library, please join the **#lib_pydp** Slack channel.
- If you’d like to follow along with any code changes to the library, please join the **#code_dp_python** Slack channel.

### Issues

On <https://github.com/OpenMined/PyDP/issues> you can find all open Issues. Find a detailed explanation on how to work with issues below, under [Issue Allocation](#issue-allocation).


# About PyDP

The project uses [Pybind11](http://pybind11.readthedocs.io) to wrap Google's [Differential Privacy](https://github.com/google/differential-privacy) library.

The library is written in C++, so it is best you have some familiarity with that language before attempting to help out here.

You can check out [here](https://www.learncpp.com/) to get your started about C++.

Regarding Pybind, Here is a good [introduction](https://www.youtube.com/watch?v=jQedHfF1Jfw) about it.


## Setup

### Forking a Repository

To contribute to PyDP you will need to fork the OpenMind/PyDP repository.
Then you can work risk-free on your fork.

Fork the repository and run `git fetch upstream` followed by `git pull 'branch-name'` before you begin your work, to get the remote changes on your local machine.

**Note:** All of PyDP work is done on :dev branch.

### Syncing a Forked Repository

To sync your fork with the OpenMined/PyDP repository please see this [Guide](https://help.github.com/articles/syncing-a-fork/) on how to sync your fork.

### Installing Script

This script automates the installation of the prerequisite packages to get you started, you can optionally install these manually referring to the list in the said file.

If you are on Linux

```
$ ./prereqs_linux.sh  

```
If you are on OSX

```
$ ./prereqs_mac.sh
```

### Building Script

To achieve clean builds of different python versions we are using a virtualenv to isolate
the build process from system python and system libraries. Since python2 is deprecated
poetry should be looking for a python3 binary to create the virtualenv from by default.
If you want to use a specific version of python3 please refer to the
[poetry documentation](https://python-poetry.org/docs/). If you use bazel, use 3.8.0 and below.


Build the python library:

```
$ make build
```

Run the test example:
```
$ poetry run python examples/Tutorial_1-carrots_demo/carrots.py
```

Build the python wheel:

```
$ poetry run python setup.py bdist_wheel
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
$ docker build --build-arg PYTHON_VERSION=3.8 -t pydp:test .
```

To run the image:

```
$ docker run --rm -it pydp:test
```

Docker Run will allow to interact with the files; to check if your code works
perfectly, you can type:

```
$ make test
```

To run the code, you can open python interpreter inside the container by typing

```
$ python
```

Note: After each change in your code, you have to run:

```
$ docker build -t pydp:test .
```

# Contributing

### Beginner Issues

If you are new to the project and want to get into the code, we recommend picking an issue with the label "good first issue". These issues should only require general programming knowledge and little to none insights into the project.

### Issue Allocation

Each issue someone is currently working on should have an assignee. If you want to contribute to an issue someone else is already working on please make sure to get in touch with that person via slack or GitHub and organize the workflow collaboratively.

If you want to work on an open issue, please post a comment telling that you will work on that issue, we will assign you as the assignee then.

**Caution**: We try our best to keep the assignees up-to-date, but we are a group of people collaborating, delays could occur, so make sure to check the comments, before you start working on an unassigned issue.

### Coding Standards

For Naming of modules, classes and methods in Python, make sure you follow naming
conventions found
[here](https://visualgit.readthedocs.io/en/latest/pages/naming_convention.html).

For C++ Styling, we follow Google's coding standard. Read more about it
[here](./.clang-format).

For Python Formatting, we use
[Black](https://black.readthedocs.io/en/stable/the_black_code_style.html),
a stricter subset of PEP8.

### Keep it DRY (Don't repeat yourself)

As with any software project, it's important to keep the amount of code to a minimum, so keep code duplication to a minimum!

### Creating a Pull Request

At any point in time you can create a pull request, so others can see your changes and give you feedback.
Please create all pull requests to the `dev` branch.

If your PR is still work in progress and not ready to be merged please add a `[WIP]` at the start of the title.
Example:`[WIP] BoundedMean error check`

***Always fill the PR template before sending a PR for better review and understanding :***
- Description - summary of the change, the motivation, and any additionl context that will help others understand your PR
- Affected Dependencies - List any dependencies that are required for this change.
- **How has this been tested? (Important)**
   - Describe the tests that you ran to verify your changes.
   - Provide instructions so we can reproduce.
   - List any relevant details for your test configuration.
- Checklist - Following the code of conduct and basic guidelines.


### Check CI and Wait for Reviews

After each commit GitHub Actions will check your new code against the formatting guidelines and execute the tests to check if the test coverage is high enough.

***We will only merge PRs that pass ALL the GitHub Actions checks.***

If your check fails, don't worry, you will still be able to make changes and make your code pass the checks. Feel free to ask around in the Slack channel **#lib_pydp**.

Note: It is always suggested to run black or clang format test or pytest on the code before sending a PR.

### Check the Docs
We are using (Sphinx)[https://www.sphinx-doc.org/en/master/] to generate the docs. A github action builds these on based on the `dev` branch. In order to check that your docstring are correctly processed you can build the docs locally.
Run
```
cd docs/ && make html && make serve
``` 
and navigate to `localhost:8000` in a browser to view the docs.
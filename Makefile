.PHONY: clean clean-test clean-pyc clean-build docs help
.DEFAULT_GOAL := help

define BROWSER_PYSCRIPT
import os, webbrowser, sys

try:
	from urllib import pathname2url
except:
	from urllib.request import pathname2url

webbrowser.open("file://" + pathname2url(os.path.abspath(sys.argv[1])))
endef
export BROWSER_PYSCRIPT

define PRINT_HELP_PYSCRIPT
import re, sys

for line in sys.stdin:
	match = re.match(r'^([a-zA-Z_-]+):.*?## (.*)$$', line)
	if match:
		target, help = match.groups()
		print("%-20s %s" % (target, help))
endef
export PRINT_HELP_PYSCRIPT

BROWSER := pipenv run python -c "$$BROWSER_PYSCRIPT"

help:
	@pipenv run python -c "$$PRINT_HELP_PYSCRIPT" < $(MAKEFILE_LIST)

build: ## compile bindings and genearte Python module
	./build_PyDP.sh

clean: clean-build clean-pyc clean-test ## remove all build, test, coverage and Python artifacts

clean-build: ## remove build artifacts
	rm -fr build/
	rm -fr dist/
	rm -fr .eggs/
	find . -name '*.egg-info' -exec rm -fr {} +
	find . -name '*.egg' -exec rm -f {} +

clean-pyc: ## remove Python file artifacts
	find . -name '*.pyc' -exec rm -f {} +
	find . -name '*.pyo' -exec rm -f {} +
	find . -name '*~' -exec rm -f {} +
	find . -name '__pycache__' -exec rm -fr {} +

clean-test: ## remove test and coverage artifacts
	rm -f .coverage
	rm -fr htmlcov/
	rm -fr .pytest_cache

format-style-python: ## format Python files code style in-place
	@ pipenv run black ./

format-style-cpp: ## format C++ files code style in-place
	@ find ./src/bindings/ -iname *.hpp -o -iname *.cpp -o -iname *.h -o -iname *.cc | \
	pipenv run xargs clang-format -i -style='file'

check-style-python: ## check for Python code style in-place
	@ echo "\e[36mChecking Python code style.\e[0m" && \
	pipenv run black ./ --check --diff || \
	( echo "\e[33mRun \e[36mmake format-style-python\e[33m to fix style errors.\e[0m"; \
	  exit 1 )

check-style-cpp: ## check for C++ code style in-place
	@ echo "\e[36mChecking C++ code style.\e[0m" && \
	pipenv run ./run-clang-format.py -r src/bindings/ || \
	( echo "\e[33mRun \e[34mmake format-style-cpp\e[33m to fix style errors.\e[0m"; \
	  exit 1 )

run-tests-only: install ## run tests without style tests
	pipenv run pytest tests

test: check-style-python check-style-cpp run-tests-only ## check style and run tests

release: dist ## package and upload a release
	twine upload dist/*

dist: clean ## builds source and wheel package
	pipenv run python setup.py sdist
	pipenv run python setup.py bdist_wheel
	ls -l dist

install: clean ## install the package to the active Python's site-packages
	pipenv run python setup.py install

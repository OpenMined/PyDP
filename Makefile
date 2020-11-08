include .env # Read .env file

.PHONY: build clean clean-test clean-pyc clean-build docs help
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

BROWSER := poetry run python -c "$$BROWSER_PYSCRIPT"

help:
	@poetry run python -c "$$PRINT_HELP_PYSCRIPT" < $(MAKEFILE_LIST)

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
	find . -name '*.gcov' -exec rm -fr {} +

format-style-python: ## format Python files code style in-place
	@ poetry run black ./

format-style-cpp: ## format C++ files code style in-place
	@ find ./src/bindings/ -iname *.hpp -o -iname *.cpp -o -iname *.h -o -iname *.cc | \
	xargs clang-format -i -style='file'

check-style-python: ## check for Python code style in-place
	@ echo "\e[36mChecking Python code style.\e[0m" && \
	poetry run black ./ --check --diff || \
	( echo "\e[33mRun \e[36mmake format-style-python\e[33m to fix style errors.\e[0m"; \
	  exit 1 )

check-style-cpp: ## check for C++ code style in-place
	@ echo "\e[36mChecking C++ code style.\e[0m" && \
	poetry run ./run-clang-format.py -r src/bindings/ || \
	( echo "\e[33mRun \e[34mmake format-style-cpp\e[33m to fix style errors.\e[0m"; \
	  exit 1 )

check-coverage-python: ## check for Python code coverage
	@ echo "\e[36mChecking Python code coverage with MIN_COVERAGE=${MIN_COVERAGE}.\e[0m" && \
	poetry run coverage report --fail-under ${MIN_COVERAGE} || \
	( echo "\e[33mRun \e[34mmake show-coverage\e[33m to see a detailed HTML coverage report.\e[0m"; \
		exit 1 )

check-coverage-cpp: ## check for C++ code coverage
	@ echo "\e[36mChecking C++ code style with MIN_COVERAGE=${MIN_COVERAGE}.\e[0m" && \
	mkdir -p coverage_report/cpp && \
	poetry run gcovr --print-summary --fail-under-line ${MIN_COVERAGE} || \
	( echo "\e[33mRun \e[34mmake show-coverage\e[33m to see a detailed HTML coverage report.\e[0m"; \
		exit 1 )

run-tests-only: install ## run tests with coverage generation and without style tests
	poetry run coverage run -m pytest tests

test: check-style-python check-style-cpp run-tests-only check-coverage-python check-coverage-cpp ## check style and run tests

show-coverage: ## report code coverage
	echo "\e[36mGenerating code coverage HTML report.\e[0m"
	poetry run coverage html -d coverage_report/python
	poetry run gcovr --html-details coverage_report/cpp/index.html
	$(BROWSER) coverage_report/index.html

release: dist ## package and upload a release
	twine upload dist/*

dist: clean ## builds source and wheel package
	poetry run python setup.py sdist
	poetry run python setup.py bdist_wheel
	ls -l dist

install: dist ## install the package to the active Python's site-packages
	poetry run pip install --upgrade --force-reinstall dist/*.whl

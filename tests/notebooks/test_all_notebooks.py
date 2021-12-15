# stdlib
import glob
import os
import subprocess
import tempfile

# third party
import black
import mypy
import nbqa

# # execute notebook in given path
# def _execute_notebook(notebook_path: str) -> bool:
#     # convert notebook-under-test in path to a temp notebook and execute it
#     with tempfile.NamedTemporaryFile(suffix=".ipynb") as fout:
#         args = [
#             "jupyter",
#             "nbconvert",
#             "--to",
#             "notebook",
#             "--execute",
#             "--output",
#             fout.name,
#             notebook_path,
#         ]
#     subprocess.check_call(args)

#     # return true if execution is successful
#     return True


# # return all .ipynb notebooks in a given folder
# def _get_all_notebooks(path: str) -> list:
#     # recursively find all .ipynb files in a given path's subdirectories
#     notebook_paths = glob.glob(os.path.join(path, "./**/*.ipynb"), recursive=True)

#     return notebook_paths


# # test all notebooks in a given path
# def test_all_notebooks(path="examples/"):
#     # get all notebooks under path
#     notebook_paths = _get_all_notebooks(path)

#     # execute each notebook
#     for notebook_path in notebook_paths:
#         # make sure notebook is successfully executed
#         assert _execute_notebook(notebook_path)

#     # execute each notebook
#     for notebook_path in notebook_paths:
#         # mypy tests for all notebooks in a given path
#         subprocess.run("nbqa mypy " + notebook_path, shell=True)

#     for notebook_path in notebook_paths:
#         # black tests to search for differences for all notebooks in a given path
#         subprocess.run("nbqa black " + notebook_path + " --nbqa-diff", shell=True)

#     for notebook_path in notebook_paths:
#         # black tests to modify the outputs for all notebooks in a given path
#         subprocess.run("nbqa black " + notebook_path + " --nbqa-mutate", shell=True)

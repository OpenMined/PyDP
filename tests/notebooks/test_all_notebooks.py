import os
import subprocess
import tempfile
import glob

# execute notebook in given path
def _execute_notebook(notebookPath: str) -> bool:
    # convert notebook-under-test in path to a temp notebook and execute it
    with tempfile.NamedTemporaryFile(suffix=".ipynb") as fout:
        args = [
            "jupyter",
            "nbconvert",
            "--to",
            "notebook",
            "--execute",
            "--output",
            fout.name,
            notebookPath,
        ]
        subprocess.check_call(args)

    # return true if execution is successful
    return True


# return all .ipynb notebooks in a given folder
def _get_all_notebooks(path: str) -> list:
    # recursively find all .ipynb files in a given path's subdirectories
    notebookPaths = glob.glob(os.path.join(path, "./**/*.ipynb"), recursive=True)

    return notebookPaths


# test all notebooks in a given path
def test_all_notebooks(path="examples/"):
    # get all notebooks under path
    notebookPaths = _get_all_notebooks(path)

    # execute each notebook
    for notebookPath in notebookPaths:
        # make sure notebook is successfully executed
        assert _execute_notebook(notebookPath)

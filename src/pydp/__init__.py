from pydp import algorithms, distributions, util


__version__ = "1.0.2"


import sys

# assert sys.version_info >= (3, 6)
if sys.version_info < (3, 6):
    print(
        "WARN: Support for Python 3.5 and below is being deprecated. \
        Please upgrade your version."
    )

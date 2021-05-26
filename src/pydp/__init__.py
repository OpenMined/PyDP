# stdlib
import sys

# pydp absolute
from pydp import algorithms
from pydp import distributions
from pydp import util

__version__ = "1.0.2"


# assert sys.version_info >= (3, 6)
if sys.version_info < (3, 6):
    print(
        "WARN: Support for Python 3.5 and below is being deprecated. \
        Please upgrade your version."
    )

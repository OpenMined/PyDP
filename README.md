![Tests](https://img.shields.io/github/workflow/status/OpenMined/PyDP/Tests)
![Version](https://img.shields.io/github/v/tag/OpenMined/PyDP?color=green&label=pypi)
![License](https://img.shields.io/github/license/OpenMined/PyDP)

# PyDP

In today's data-driven world, more and more researchers and data scientists
use machine learning to create better models or more innovative solutions for
a better future.

These models often tend to handle sensitive or personal data, which can cause
privacy issues. For example, some AI models can memorize details about
the data they've been trained on and could potentially leak these details later
on.

To help measure sensitive data leakage and reduce the possibility of it
happening, there is a mathematical framework called differential privacy.

In 2020, OpenMined created a Python wrapper for Google's [Differential
Privacy](https://github.com/google/differential-privacy) project called PyDP.
The library provides a set of ε-differentially private algorithms, which can be
used to produce aggregate statistics over numeric data sets containing private
or sensitive information. Therefore, with PyDP you can control the privacy
guarantee and accuracy of your model written in Python.

**Things to remember about PyDP:**

- :rocket: Features differentially private algorithms including: BoundedMean,
BoundedSum, Max, Count Above, Percentile, Min, Median, etc.
  - All the computation methods mentioned above use Laplace noise only (other
noise mechanisms will be added soon! :smiley:)
- :fire: Compatible with all three types of Operating Systems - Linux, macOS, and Windows :smiley:
- :star: Use Python 3.x.

## Installation

To install PyDP, use the [PyPI](https://pip.pypa.io/en/stable/) package manager:

```bash
pip install python-dp
```

(If you have `pip3` separately for Python 3.x, use `pip3 install python-dp`.)

## Examples

Refer to the
[curated list](https://github.com/OpenMined/PyDP/tree/dev/examples)
of tutorials and sample code to learn more about the PyDP library.

You can also get started with
[an introduction to PyDP](https://github.com/OpenMined/PyDP/blob/dev/examples/Tutorial_1-carrots_demo/carrots_demo.ipynb)
(a Jupyter notebook) and
[the carrots demo](https://github.com/OpenMined/PyDP/blob/dev/examples/Tutorial_1-carrots_demo/carrots.py)
(a Python file).

Example: calculate the Bounded Mean

```python
# Import PyDP
import pydp as dp
# Import the Bounded Mean algorithm
from pydp.algorithms.laplacian import BoundedMean

# Calculate the Bounded Mean
# Structure: `BoundedMean(epsilon: double, lower: int, upper: int)`
# `epsilon`: a Double, between 0 and 1, denoting the privacy threshold,
#            measures the acceptable loss of privacy (with 0 meaning no loss is acceptable)
# `lower` and `upper`: Integers, representing lower and upper bounds, respectively
x = BoundedMean(0.6, 1, 10)

# If the lower and upper bounds are not specified,
# PyDP automatically calculates these bounds
# x = BoundedMean(epsilon: double)
x = BoundedMean(0.6)

# Calculate the result
# Currently supported data types are integers and floats
# Future versions will support additional data types
# (Refer to https://github.com/OpenMined/PyDP/blob/dev/examples/carrots.py)
x.quick_result(input_data: list)
```

## Learning Resources

Go to [resources](https://github.com/OpenMined/PyDP/blob/dev/resources.md)
to learn more about differential privacy.

## Support and Community on Slack

If you have questions about the PyDP library, join
[OpenMined's Slack](https://slack.openmined.org) and check the
**#lib_pydp** channel. To follow the code source changes, join
**#code_dp_python**.

## Contributing

To contribute to the PyDP project, read the
[guidelines](https://github.com/OpenMined/PyDP/blob/dev/contributing.md).

Pull requests are welcome. If you want to introduce major changes, please
open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

<!-- ## Contributors -->

## License
[Apache License 2.0](https://choosealicense.com/licenses/apache-2.0/)

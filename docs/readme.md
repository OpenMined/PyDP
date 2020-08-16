![Tests](https://img.shields.io/github/workflow/status/OpenMined/PyDP/Tests)
![Version](https://img.shields.io/github/v/tag/OpenMined/PyDP?color=green&label=pypi)
![License](https://img.shields.io/github/license/OpenMined/PyDP)

## Introduction to PyDP

In today's data-driven world, data analytics is used by researchers or data scientists to create better models or innovative solutions for a better future. These models often tend to handle sensitive or personal data, which brings in some privacy concerns. For example, some AI models can memorize details about the data they've trained on and could leak these details later on. Differential privacy is a mathematical framework for measuring this privacy leakage and reducing the possibility of it happening.

This is where PyDP comes in. PyDP is a Python wrapper for Google's [Differential Privacy](https://github.com/google/differential-privacy) project. The library provides a set of ε-differentially private algorithms, which can be used to produce aggregate statistics over numeric data sets containing private or sensitive information. Thus, PyDP is helping us achieve better privacy.


**Key features of PyDP :**
- :rocket: Features differentially private algorithms including: BoundedMean, BoundedSum, Max, Count Above, Percentile, Min, Median, etc.  
- All the computation methods mentioned above use Laplace noise only. (Other noise mechanisms will be added soon... :smiley:)
- :fire: Currently supports Linux and OSX. (Windows coming real soon... :smiley:)
- :star: Supports all the Python 3+ versions.


## Installation
PyDP can be installed using the package manager [pip](https://pip.pypa.io/en/stable/) to install PyDP.

```bash
pip install python-dp
```

## Example
For a detailed representation of the features of PyDP library refer to [this example](https://github.com/OpenMined/PyDP/tree/dev/examples) .

A sample of usage can be found below:

```python
import pydp as dp # imports the DP library

# To calculate the Bounded Mean
# epsilon is a number between 0 and 1 denoting privacy threshold
# It measures the acceptable loss of privacy (with 0 meaning no loss is acceptable)
# If both the lower and upper bounds are specified, 
# x = dp.BoundedMean(epsilon: double, lower: int, upper: int)
x = dp.BoundedMean(0.6, 1, 10)

# If lower and upper bounds are not specified, 
# DP library automatically calculates these bounds
# x = dp.BoundedMean(epsilon: double)
x = dp.BoundedMean(0.6)

# To get the result
# Currently supported data types are integer and float. Future versions will support additional data types
# Refer to examples/carrots.py for an introduction
x.result(input_data: list)

```

## Learning Resources
Some of the good learning resources to get started with Python differential privacy (PyDP) project and understand the concepts behind it can be found [here](https://github.com/OpenMined/PyDP/blob/dev/resources.md).

## Support
For support in using this library, please join the **#lib_pydp** Slack channel. If you’d like to follow along with any code changes to the library, please join the **#code_dp_python** Slack channel. [Click here to join our Slack community!](https://slack.openmined.org)

## Contributing

If you'd like to contribute to this open source project please read these [guidelines](https://github.com/OpenMined/PyDP/blob/dev/contributing.md).

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

***Note : Known issue -***  If the privacy budget (epsilon is too less), we get a StatusOR error in the command line. While this needs to be raised as an error, right now, it's just displayed as an error in logs.

<!-- ## Contributors -->


## License
[Apache License 2.0](https://choosealicense.com/licenses/apache-2.0/)


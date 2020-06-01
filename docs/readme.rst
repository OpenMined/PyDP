Introduction
============

PyDP is a Python wrapper for Google’s `Differential Privacy`_ project.
The library provides a set of ε-differentially private algorithms, which
can be used to produce aggregate statistics over numeric data sets
containing private or sensitive information.

PyDP is part of the OpenMined community, come join the movement on
`Slack`_.

Instructions
============

If you’d like to contribute to this project please read these
`guidelines`_.

Usage
-----

As part of the 0.1.1 dev release, we have added all functions required in carrots demo.


To install the package: ``pip install python-dp``

::

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

Known issue: If the privacy budget (epsilon is too less), we get a
StatusOR error in the command line. While this needs to be raised as an
error, right now, it’s just displayed as an error in logs.

.. _Differential Privacy: https://github.com/google/differential-privacy
.. _Slack: http://slack.openmined.org/
.. _guidelines: https://github.com/OpenMined/PyDP/blob/master/contributing.md
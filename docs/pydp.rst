*********
PyDP
*********

Algorithms
##########
.. currentmodule:: pydp.algorithms.laplacian
.. autoclass:: BoundedMean
   :inherited-members:

.. autoclass::  BoundedSum
   :inherited-members:
.. autoclass::  BoundedStandardDeviation
   :inherited-members:
.. autoclass::  BoundedVariance
   :inherited-members:
.. autoclass::  Max
   :inherited-members:
.. autoclass::  Min
   :inherited-members:
.. autoclass::  Median
   :inherited-members:
.. autoclass::  Count
   :inherited-members:
.. autoclass::  Percentile
   :inherited-members:


Numerical Mechanisms
####################
.. currentmodule:: pydp.algorithms.numerical_mechanisms
.. autoclass:: NumericalMechanism
   :members: 
.. autoclass:: LaplaceMechanism
   :members:
   :show-inheritance:
.. autoclass:: GaussianMechanism
   :members:
   :show-inheritance:

Distributions
#############
.. currentmodule:: pydp.distributions
.. autoclass::  GaussianDistribution
   :members:
.. autoclass::  LaplaceDistribution
   :members:

Util
##########
.. automodule:: pydp.util
   :members: Geometric, UniformDouble, correlation, get_next_power_of_two, mean, order_statistics, qnorm, round_to_nearest_multiple, safe_add, safe_square, safe_subtract, standard_deviation, variance, vector_filter, vector_to_string, xor_strings


ML
##########
.. automodule:: pydp.ml.naive_bayes
.. autoclass::  GaussianNB
   :members:

Partition Selection
###################
.. currentmodule:: pydp.algorithms.partition_selection
.. autoclass:: PartitionSelectionStrategy
   :members: 
.. autofunction:: create_partition_strategy

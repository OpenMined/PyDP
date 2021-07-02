from .._pydp import _algorithms

PartitionSelectionStrategy = _algorithms.PartitionSelectionStrategy
PartitionSelectionStrategy.__doc__ = """
Provides a common abstraction for PartitionSelectionStrategy. Each partition
selection strategy class has a builder with which it can be instantiated, and
calling ShouldKeep will return true if a partition with the given number of
users should be kept based on the values the partition selection strategy
was instantiated with (while ShouldKeep will return false if the partition
should have been dropped).
"""

PartitionSelectionStrategy.ShouldKeep.__doc__ = """
ShouldKeep returns true when a partition with a given number of users
should be kept and false otherwise.
"""
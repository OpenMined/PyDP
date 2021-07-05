class PartitionSelectionStrategy:
	"""
	Base class for all (Ɛ, 𝛿)-differenially private partition selection strategies.
	"""
	def should_keep(self, num_users: int) -> bool:
		"""
		Decides whether or not to keep a partition of size `num_users` contributions
		according to the partition selection strategy.
		"""
		raise NotImplementedError


def create_truncted_geometric_partition_strategy(epsilon: float,
                                                 delta: float,
                                                 num_partitions_contributed: int) -> PartitionSelectionStrategy:
	"""
	Creates a [Truncated Geometric](https://arxiv.org/pdf/2006.03684.pdf) Partition Strategy.
	"""
	...


def create_laplace_partition_strategy(epsilon: float,
                                      delta: float,
                                      num_partitions_contributed: int) -> PartitionSelectionStrategy:
	"""
	Creates a [Laplace-Mechanism](https://github.com/google/differential-privacy/blob/main/common_docs/Delta_For_Thresholding.pdf) 
	based Partition Strategy.
	"""
	...


def create_gaussian_partition_strategy(epsilon: float,
                                       delta: float,
                                       num_partitions_contributed: int) -> PartitionSelectionStrategy:
	"""
	Creates a [Gaussian-Mechanism](https://github.com/google/differential-privacy/blob/main/common_docs/Delta_For_Thresholding.pdf)
	based Partition Strategy.
	"""
	...

def create_partition_strategy(strategy: str,
                              epsilon: float,
                              delta: float,
                              max_partitions_contributed: int) -> PartitionSelectionStrategy:
	"""
	Factory for creating PartitionSelectionStrategy.
	"""
	...

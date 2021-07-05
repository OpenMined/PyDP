from .._pydp._partition_selection import *

def create_partition_strategy(strategy: str,
							  epsilon: float,
							  delta: float,
							  max_partitions_contributed: int) -> PartitionSelectionStrategy:
	if strategy.lower() == "truncated_geometric":
		return create_truncted_geometric_partition_strategy(epsilon, delta, max_partitions_contributed)
	if strategy.lower() == "laplace":
		return create_laplace_partition_strategy(epsilon, delta, max_partitions_contributed)
	if strategy.lower() == "gaussian":
		return create_gaussian_partition_strategy(epsilon, delta, max_partitions_contributed)
	
	raise ValueError(f"Strategy '{strategy}' is not supported.")

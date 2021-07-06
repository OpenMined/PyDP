from .._pydp._partition_selection import *

def create_partition_strategy(strategy: str,
                              epsilon: float,
                              delta: float,
                              max_partitions_contributed: int) -> "PartitionSelectionStrategy":
    """
    Creates a :class:`~PartitionSelectionStrategy` instance.

    Parameters
    --------------
    strategy: str
        One of:
            * **'truncated_geomteric'**: creates a `Truncated Geometric <https://arxiv.org/pdf/2006.03684.pdf>`_ Partition Strategy.
            * **'laplace'**: creates a private partition strategy with Laplace mechanism.
            * **'gaussian'**: creates a private partition strategy with Gaussian mechanism.

    epsilon: float
        The :math:`\\varepsilon` of the partition mechanism
    delta: float
        The :math:`\\delta` of the partition mechanism
    
    max_partitions_contributed: int
        The maximum amount of partitions contributed by the strategy.    
    """
    if strategy.lower() == "truncated_geometric":
        return create_truncted_geometric_partition_strategy(epsilon, delta, max_partitions_contributed)
    if strategy.lower() == "laplace":
        return create_laplace_partition_strategy(epsilon, delta, max_partitions_contributed)
    if strategy.lower() == "gaussian":
        return create_gaussian_partition_strategy(epsilon, delta, max_partitions_contributed)

    raise ValueError(f"Strategy '{strategy}' is not supported.")

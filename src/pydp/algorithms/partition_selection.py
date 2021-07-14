from .._pydp._partition_selection import (
    create_truncated_geometric_partition_strategy,  # type: ignore
    create_laplace_partition_strategy,  # type: ignore
    create_gaussian_partition_strategy,  # type: ignore
)

__all__ = [
    "PartitionSelectionStrategy",
    "create_partition_strategy",
    "create_truncated_geometric_partition_strategy",
    "create_laplace_partition_strategy",
    "create_gaussian_partition_strategy",
]


class PartitionSelectionStrategy:
    """
    Base class for all (Ɛ, 𝛿)-differenially private partition selection strategies.
    """

    def should_keep(self, num_users: int) -> bool:
        """
        Decides whether or not to keep a partition with `num_users` based on differential privacy parameters and strategy.
        """
        ...


def create_partition_strategy(
    strategy: str, epsilon: float, delta: float, max_partitions_contributed: int
) -> "PartitionSelectionStrategy":
    """
    Creates a :class:`~PartitionSelectionStrategy` instance.

    Parameters
    --------------
    strategy:
        One of:
            * **'truncated_geomteric'**: creates a `Truncated Geometric <https://arxiv.org/pdf/2006.03684.pdf>`_ Partition Strategy.
            * **'laplace'**: creates a private partition strategy with Laplace mechanism.
            * **'gaussian'**: creates a private partition strategy with Gaussian mechanism.

    epsilon:
        The :math:`\\varepsilon` of the partition mechanism
    delta:
        The :math:`\\delta` of the partition mechanism

    max_partitions_contributed:
        The maximum amount of partitions contributed by the strategy.
    """
    if strategy.lower() == "truncated_geometric":
        return create_truncated_geometric_partition_strategy(
            epsilon, delta, max_partitions_contributed
        )
    if strategy.lower() == "laplace":
        return create_laplace_partition_strategy(
            epsilon, delta, max_partitions_contributed
        )
    if strategy.lower() == "gaussian":
        return create_gaussian_partition_strategy(
            epsilon, delta, max_partitions_contributed
        )

    raise ValueError(f"Strategy '{strategy}' is not supported.")

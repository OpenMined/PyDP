import typing

from .._pydp._partition_selection import (
    create_truncated_geometric_partition_strategy,  # type: ignore
    create_laplace_partition_strategy,  # type: ignore
    create_gaussian_partition_strategy,  # type: ignore
    create_pre_thresholding_partition_strategy,  # type: ignore
    PartitionSelectionStrategyType,  # type: ignore
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
        raise NotImplementedError("PartitionSelectionStrategy is an abstract class.")


def create_partition_strategy(
    strategy: str,
    epsilon: float,
    delta: float,
    max_partitions_contributed: int,
    pre_threshold: typing.Optional[int] = None,
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

    pre_threshold:
        The minimum amount of privacy units which require for keeping dataset.
        More details on pre-thresholding are in
        https://github.com/google/differential-privacy/blob/main/common_docs/pre_thresholding.md
    """
    if pre_threshold is not None:
        strategy_type = _to_partition_selection_strategy_type(strategy)
        return create_pre_thresholding_partition_strategy(
            epsilon, delta, max_partitions_contributed, pre_threshold, strategy_type
        )
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


def _to_partition_selection_strategy_type(s: str) -> PartitionSelectionStrategyType:
    if s.lower() == "truncated_geometric":
        return PartitionSelectionStrategyType.NEAR_TRUNCATED_GEOMETRIC
    if s.lower() == "laplace":
        return PartitionSelectionStrategyType.LAPLACE
    if s.lower() == "gaussian":
        return PartitionSelectionStrategyType.GAUSSIAN
    raise ValueError(f"Strategy '{s}' is not supported.")

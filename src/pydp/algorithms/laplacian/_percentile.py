# stdlib
from typing import Union

# pydp relative
from .._algorithm import MetaAlgorithm


class Percentile(MetaAlgorithm):
    """
    Perencetile finds the value in the dataset with that percentile, in a differentially private manner.
    """

    def __init__(
        self,
        epsilon: float = 1.0,
        percentile: float = 0.0,
        lower_bound: Union[int, float, None] = None,
        upper_bound: Union[int, float, None] = None,
        dtype: str = "int",
    ):
        super().__init__(
            epsilon=epsilon,
            percentile=percentile,
            lower_bound=lower_bound,
            upper_bound=upper_bound,
            dtype=dtype,
        )

    @property
    def percentile(self) -> float:
        """
        percentile Gets the value that was set in the constructor.
        """
        return self._MetaAlgorithm__algorithm.percentile  # type: ignore

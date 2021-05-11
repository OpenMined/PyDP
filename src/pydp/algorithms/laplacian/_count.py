# stdlib
from typing import Union

# pydp relative
from .._algorithm import MetaAlgorithm


class Count(MetaAlgorithm):
    """
    Count computes the Count of number of items in the dataset, in a differentially private manner.
    """

    def __init__(
        self,
        epsilon: float = 1.0,
        l0_sensitivity: int = 1,
        linf_sensitivity: int = 1,
        dtype: str = "int",
    ):
        super().__init__(
            epsilon=epsilon,
            l0_sensitivity=l0_sensitivity,
            linf_sensitivity=linf_sensitivity,
            dtype=dtype,
        )

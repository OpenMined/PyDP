from functools import wraps

from .._pydp import _algorithms


class WrapAlgorithm:

    # Class variables
    __methods_to_wrap = [
        "epsilon",
        "privacy_budget_left",
        "memory_used",
        "add_entries",
        "add_entry",
        "result",
        "partial_result",
        "reset",
        "serialize",
        "merge",
        "noise_confidence_interval",
    ]

    def __init__(self, dtype="int", **kwargs):
        binded_class = f"{self.__class__.__name__}{self.__map_dtype_str(dtype)}"
        class_ = getattr(_algorithms, binded_class)

        self.dtype = dtype
        self.__algorithm = class_(**kwargs)

        for method in self.__methods_to_wrap:
            setattr(self, method, getattr(self.__algorithm, f"{method}"))

    @staticmethod
    def __map_dtype_str(dtype):
        if dtype == "int":
            return "Int"
        elif dtype == "float":
            return "Double"
        else:
            raise RuntimeError(f"dtype: {dtype} is not supported")


class Algorithm(WrapAlgorithm):
    def __init__(self, epsilon=1.0, dtype="int"):
        WrapAlgorithm.__init__(self, dtype=dtype, epsilon=epsilon)


class BoundedAlgorithm(WrapAlgorithm):
    def __init__(self, epsilon=1.0, lower_bound=None, upper_bound=None, dtype="int"):
        WrapAlgorithm.__init__(
            self,
            dtype=dtype,
            epsilon=epsilon,
            lower_bound=lower_bound,
            upper_bound=upper_bound,
        )

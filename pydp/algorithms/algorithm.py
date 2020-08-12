from functools import wraps

from .._pydp import _algorithms


class Algorithm:

    # Class variables
    __methods_to_wrap = [
        "epsilon",
        "privacy_budget_left",
        "memory_used",
        "add_entries",
        "add_entry",
        "result",
        "partial_result",
        "consume_privacy_budget",
        "reset",
        "serialize",
        "merge",
        "noise_confidence_interval",
    ]

    def __init__(self, dtype="int", **kwargs):
        cpp_class_name = f"{self.__class__.__name__}{self.__map_type_str(dtype)}"
        class_ = getattr(_algorithms, cpp_class_name)

        self.dtype = dtype
        self.__algorithm = class_(**kwargs)

        for method in self.__methods_to_wrap:
            setattr(self, method, getattr(self.__algorithm, f"{method}"))

    @staticmethod
    def __map_type_str(type):
        if type == "int":
            return "Int"
        elif type == "float":
            return "Double"
        else:
            raise RuntimeError(f"dtype: {dtype} is not supported")

__all__ = ["Count"]


class Count:
    def __init__(self, epsilon=1.0, dtype="int"):
        from ..pydp import _algorithms

        if dtype == "int":
            self.__algorithm = _algorithms.CountInt(epsilon)
        elif dtype == "float":
            self.__algorithm = _algorithms.CountDouble(epsilon)
        else:
            raise RuntimeError(f"dtype: {dtype} is not supported")

    def result(self, list):
        return self.__algorithm.result(list)

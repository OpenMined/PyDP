from ..._pydp import _algorithms


def map_type_str(type):
    if type == "int":
        return "Int"
    elif type == "float":
        return "Double"
    else:
        raise RuntimeError(f"dtype: {dtype} is not supported")


class Count:
    def __init__(self, epsilon=1.0, dtype="int"):
        class_ = getattr(_algorithms, f"Count{map_type_str(dtype)}")

        self.dtype = dtype
        self.__algorithm = class_(epsilon)

    def result(self, list):
        return self.__algorithm.result(list)

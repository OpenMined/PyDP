from ..._pydp import _algorithms
from .helper import map_type_str

class Count:
    def __init__(self, epsilon=1.0, dtype="int"):
        class_ = getattr(_algorithms, f"Count{map_type_str(dtype)}")

        self.dtype = dtype
        self.__algorithm = class_(epsilon)

    def result(self, list):
        return self.__algorithm.result(list)

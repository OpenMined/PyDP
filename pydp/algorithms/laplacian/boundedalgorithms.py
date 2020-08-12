from ..._pydp import _algorithms
from .helper import map_type_str

class Bounded:
    def __init__(self, algorithm, epsilon=1.0, lower_bound = None, upper_bound = None, dtype="int"):
        class_ = getattr(_algorithms, f"{algorithm}{map_type_str(dtype)}")

        self.dtype = dtype
        self.__algorithm = class_(epsilon, lower_bound, upper_bound)

    def result(self, list):
        return self.__algorithm.result(list)

class BoundedMean(Bounded):
    def __init__(self, epsilon=1.0, lower_bound = None, upper_bound = None, dtype="int"):
        super().__init__("BoundedMean", epsilon, lower_bound, upper_bound, dtype)


class BoundedSum(Bounded):
    def __init__(self, epsilon=1.0, lower_bound = None, upper_bound = None, dtype="int"):
        super().__init__("BoundedSum", epsilon, lower_bound, upper_bound, dtype)

class BoundedStandardDeviation(Bounded):
    def __init__(self, epsilon=1.0, lower_bound = None, upper_bound = None, dtype="int"):
        super().__init__("BoundedStandardDeviation", epsilon, lower_bound, upper_bound, dtype)

class BoundedVariance(Bounded):
    def __init__(self, epsilon=1.0, lower_bound = None, upper_bound = None, dtype="int"):
        super().__init__("BoundedVariance", epsilon, lower_bound, upper_bound, dtype)
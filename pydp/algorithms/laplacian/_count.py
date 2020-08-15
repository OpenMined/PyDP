from .._algorithm import MetaAlgorithm


class Count(MetaAlgorithm):
    '''
    Count Explaination
    TODO
    '''
    def __init__(self, epsilon: float=1.0, dtype: str="int"):
        super().__init__(epsilon=epsilon, dtype=dtype)

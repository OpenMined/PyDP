from .._pydp import _algorithms


class MetaAlgorithm:
    def __init__(self, **kwargs):
        dtype = kwargs.pop("dtype")

        # Delete bound params if the are not set to avoid  conflicts with builder
        if kwargs["lower_bound"] is None:
            kwargs.pop("lower_bound")
        if kwargs["upper_bound"] is None:
            kwargs.pop("upper_bound")

        binded_class = f"{self.__class__.__name__}{self.__map_dtype_str(dtype)}"
        class_ = getattr(_algorithms, binded_class)

        self.dtype = dtype
        self.__algorithm = class_(**kwargs)
        self.epsilon = self.__algorithm.epsilon

    @staticmethod
    def __map_dtype_str(dtype):
        if dtype == "int":
            return "Int"
        elif dtype == "float":
            return "Double"
        else:
            raise RuntimeError(f"dtype: {dtype} is not supported")

    def privacy_budget_left(self):
        """
        Returns the remaining privacy budget.
        """
        return self.__algorithm.privacy_budget_left()

    def memory_used(self):
        """
        Returns the memory currently used by the algorithm in bytes.
        """
        return self.__algorithm.memory_used()

    def add_entries(self, list):
        """
        Adds multiple inputs to the algorithm.
        """
        return self.__algorithm.add_entries(list)

    def add_entry(self, value):
        """
        Adds one input to the algorithm.
        """
        return self.__algorithm.add_entry(value)

    def result(self, list):
        """
        Runs the algorithm on the input using the epsilon parameter provided in the constructor and returns output.

        Consumes 100% of the privacy budget.
        """
        return self.__algorithm.result(list)

    def partial_result(self):
        """
        Gets the algorithm result, consuming the remaining privacy budget.
        """
        return self.__algorithm.partial_result()

    def partial_result(self, privacy_budget):
        """
        Same as above, but consumes only the `privacy_budget` amount of budget.

        Privacy budget, defined on [0,1], represents the fraction of the total budget to consume.
        """
        return self.__algorithm.partial_result(privacy_budget)

    def partial_result(self, privacy_budget, noise_interval_level):
        """
        Same as above, but provides the confidence level of the noise confidence interval, which may be included in the algorithm output.
        """
        return self.__algorithm.partial_result(privacy_budget, noise_interval_level)

    def reset(self):
        """
        Resets the algorithm to a state in which it has received no input. After Reset is called, the algorithm should only consider input added after the last Reset call when providing output.
        """
        return self.__algorithm.reset()

    def serialize(self):
        """
        Serializes summary data of current entries into Summary proto. This allows results from distributed aggregation to be recorded and later merged.

        Returns empty summary for algorithms for which serialize is unimplemented.
        """
        return self.__algorithm.serialize()

    def merge(self, summary):
        """
        Merges serialized summary data into this algorithm. The summary proto must represent data from the same algorithm type with identical parameters. The  data field must contain the algorithm summary type of the corresponding algorithm used. The summary proto cannot be empty.
        """
        return self.__algorithm.merge(summary)

    def noise_confidence_interval(self, confidence_level, privacy_budget):
        """
        Returns the confidence_level confidence interval of noise added within the algorithm with specified privacy budget, using epsilon and other relevant, algorithm-specific parameters (e.g. bounds) provided by the constructor.

        This metric may be used to gauge the error rate introduced by the noise.

        If the returned value is <x,y>, then the noise added has a confidence_level chance of being in the domain [x,y].

        By default, NoiseConfidenceInterval() returns an error. Algorithms for which a confidence interval can feasibly be calculated override this and output the relevant value.

        Conservatively, we do not release the error rate for algorithms whose confidence intervals rely on input size.
        """
        return self.__algorithm.noise_confidence_interval(
            confidence_level, privacy_budget
        )


class Algorithm(MetaAlgorithm):
    def __init__(self, epsilon=1.0, dtype="int"):
        super().__init__(epsilon=epsilon, dtype=dtype)


class BoundedAlgorithm(MetaAlgorithm):
    def __init__(self, epsilon=1.0, lower_bound=None, upper_bound=None, dtype="int"):
        super().__init__(
            epsilon=epsilon,
            lower_bound=lower_bound,
            upper_bound=upper_bound,
            dtype=dtype,
        )

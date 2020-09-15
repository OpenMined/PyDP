from .._algorithm import BoundedAlgorithm


class BoundedMean(BoundedAlgorithm):
    """
    BoundedMean computes the average of values in a dataset, in a differentially private manner.

    Incrementally provides a differentially private average.
    All input vales are normalized to be their difference from the middle of the
    input range. That allows us to calculate the sum of all input values with
    half the sensitivity it would otherwise take for better accuracy (as compared
    to doing noisy sum / noisy count). This algorithm is taken from section 2.5.5
    of the following book (algorithm 2.4):
    https://books.google.com/books?id=WFttDQAAQBAJ&pg=PA24#v=onepage&q&f=false

    """

    pass


class BoundedSum(BoundedAlgorithm):
    """
    BoundedSum computes the sum of values in a dataset, in a differentially private manner.

    Incrementally provides a differentially private sum, clamped between upper
    and lower values. Bounds can be manually set or privately inferred.
    """

    pass


class BoundedStandardDeviation(BoundedAlgorithm):
    """
    BoundedStandardDeviation computes the standard deviation of values in a dataset, in a differentially private manner.

    Incrementally provides a differentially private standard deviation for values
    in the range [lower..upper]. Values outside of this range will be clamped so
    they lie in the range. The output will also be clamped between 0 and (upper -
    lower).

    The implementation simply computes the bounded variance and takes the square
    root, which is differentially private by the post-processing theorem. It
    relies on the fact that the bounded variance algorithm guarantees that the
    output is non-negative.
    """

    pass


class BoundedVariance(BoundedAlgorithm):
    """
    BoundedVariance computes the variance of values in a dataset, in a differentially private manner.

    Incrementally provides a differentially private variance for values in the
    range [lower..upper]. Values outside of this range will be clamped so they
    lie in the range. The output will also be clamped between 0 and (upper -
    lower)^2. Since the result is guaranteed to be positive, this algorithm can
    be used to compute a differentially private standard deviation.

    The algorithm uses O(1) memory and runs in O(n) time where n is the size of
    the dataset, making it a fast and efficient. The amount of noise added grows
    quadratically in (upper - lower) and decreases linearly in n, so it might not
    produce good results unless n >> (upper - lower)^2.

    The algorithm is a variation of the algorithm for differentially private mean
    from "Differential Privacy: From Theory to Practice", section 2.5.5:
    https://books.google.com/books?id=WFttDQAAQBAJ&pg=PA24#v=onepage&q&f=false
    """

    pass


class Max(BoundedAlgorithm):
    """
    Max computes the Max value in the dataset, in a differentially private manner.
    """

    pass


class Min(BoundedAlgorithm):
    """
    Min computes the minium value in the dataset, in a differentially private manner.
    """

    pass


class Median(BoundedAlgorithm):
    """
    Median computes the Median value in the dataset, in a differentially private manner.
    """

    pass

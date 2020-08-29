"""
 Important to note that python's float type has the same precision as the C++
 double.
"""

import sys  # isort:skip

sys.path.append("../pydp")  # isort:skip

import os
import statistics as s
from pathlib import Path

import pandas as pd
import pydp as dp  # our privacy library
from pydp.algorithms.laplacian import BoundedSum, BoundedMean, Count, Max

# Creating a class ClassReporter


class CarrotReporter:

    # Function to read the csv file and creating a dataframe
    def __init__(self, data_filename, epsilon):
        self.data_filename = data_filename
        self.epsilon = epsilon
        self._epsilon = epsilon
        self._privacy_budget = float(1.0)

        self._df = pd.read_csv(
            self.data_filename, sep=",", names=["animal", "carrots_eaten"]
        )

    # Function to return total number of carrots in dataset.
    def sum_carrots(self) -> int:
        return self._df.sum()[1]

    # Function to return mean of the carrots in the dataset.
    def mean_carrots(self) -> float:
        return s.mean(list(self._df["carrots_eaten"]))

    # Function to calculate total number of carrots above a particular row.
    def count_above(self, limit: int) -> int:
        return self._df[self._df.carrots_eaten > limit].count()[0]

    # Function to calculate maximum number of carrots in the column.
    def max(self) -> int:
        return self._df.max()[1]

    # Function to return the remaining privacy budget.
    def privacy_budget(self) -> float:
        return self._privacy_budget

    # Function to return the DP sum of all carrots eaten.
    def private_sum(self, privacy_budget: float) -> float:
        x = BoundedSum(privacy_budget, dtype="float")
        return x.quick_result(list(self._df["carrots_eaten"]))

    # Function to return the DP mean of all carrots eaten.
    def private_mean(self, privacy_budget: float) -> float:
        x = BoundedMean(privacy_budget, dtype="float")
        return x.quick_result(list(self._df["carrots_eaten"]))

    # Function to return the DP count of the number of animals who ate more than "limit" carrots.
    def private_count_above(self, privacy_budget: float, limit: int) -> int:
        x = Count(privacy_budget, dtype="int")
        return x.quick_result(
            list(self._df[self._df.carrots_eaten > limit]["carrots_eaten"])
        )

    # Function to return the DP maximum of the number of carrots eaten by any one animal.
    def private_max(self, privacy_budget: float) -> int:
        # 0 and 150 are the upper and lower limits for the search bound.
        x = Max(privacy_budget, 0, 150, dtype="int")
        return x.quick_result(list(self._df["carrots_eaten"]))


# get absolute path
path = Path(os.path.dirname(os.path.abspath(__file__)))

c = CarrotReporter(path / "animals_and_carrots.csv", 1)
print("Mean:\t" + str(c.mean_carrots()))
print("Private Mean:\t" + str(c.private_mean(1)))

print("Sum:\t" + str(c.sum_carrots()))
print("Private Sum:\t" + str(c.private_sum(1)))

print("(Count) Above 70 values:\t" + str(c.count_above(70)))
print("private Count Above:\t" + str(c.private_count_above(1, 70)))

print("Max:\t" + str(c.max()))
print("Private Max:\t" + str(c.private_max(1)))

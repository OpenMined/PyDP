# important to note that python's float type has the same precision as the C++ double

import pydp as dp    # our privacy library
import pandas as pd

class CarrotReporter:  # Creating a class ClassReporter

    data_filename: str
    epsilon: float

    def __init__(self, data_filename, epsilon): #Function to read the csv file and creating a dataframe
        self.data_filename = data_filename
        self.epsilon=epsilon
        self._epsilon=epsilon
        self._df = pd.read_csv(self.data_filename, sep=',', names=['animal', 'carrots_eaten'])

    def sum_carrots(self) -> int:  # Function to return total number of carrots in dataset.
        return self._df.sum()[1]

    def mean_carrots(self) -> float: # Function to return mean of the carrots in the dataset.
        return self._df.mean()[0]

    def count_above(self, limit: int) -> int:  # Function to calculate total number of carrots above a particular row.
        return self._df[self._df.carrots_eaten>limit].count()[0]

    def max(self) -> int:     # Function to calculate maximum number of carrots in the column.
        return self._df.max()[1]

    def privacy_budget(self) -> float:
        return self._privacy_budget

    def private_sum(self, privacy_budget: float) -> dp.StatusOrO: pass
    def private_mean(self, privacy_budget: float) -> dp.StatusOrO: pass
    def private_count_above(self, privacy_budget: float, limit: int) -> dp.StatusOrO: pass
    def private_max(self, privacy_budget: float) -> dp.StatusOrO: pass

    _epsilon: float
    _privacy_budget = float(1)
    _df: pd.DataFrame


c = CarrotReporter("animals_and_carrots.csv", 1)
print("Mean:\t" + str(c.mean_carrots()))
print("Sum:\t" + str(c.sum_carrots()))
print("Above 70:\t" + str(c.count_above(70)))
print("Max:\t" + str(c.max()))

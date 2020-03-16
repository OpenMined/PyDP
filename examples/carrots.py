# important to note that python's float type has the same precision as the C++ double

# our privacy library
import pydp as dp
import pandas as pd

 # Creating a class ClassReporter
class CarrotReporter:

    data_filename: str
    epsilon: float

    #Function to read the csv file and creating a dataframe
    def __init__(self, data_filename, epsilon):
        self.data_filename = data_filename
        self.epsilon=epsilon
        self._epsilon=epsilon
        self._df = pd.read_csv(self.data_filename, sep=',', names=['animal', 'carrots_eaten'])

    # Function to return total number of carrots in dataset.
    def sum_carrots(self) -> int:
        return self._df.sum()[1]

    # Function to return mean of the carrots in the dataset.
    def mean_carrots(self) -> float:
        return self._df.mean()[0]

    # Function to calculate total number of carrots above a particular row.
    def count_above(self, limit: int) -> int:
        return self._df[self._df.carrots_eaten>limit].count()[0]

     # Function to calculate maximum number of carrots in the column.
    def max(self) -> int:
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

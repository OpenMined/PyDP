import pydp as dp
from pydp.algorithms.laplacian import BoundedSum, Count

import math
import statistics as s
import pandas as pd
from collections import defaultdict

# An hour when visitors start entering the restaurant (900 represents 9:00 AM)
OPENING_HOUR = 900

# An hour when visitors stop entering the restaurant (2000 represents 20:00 PM)
CLOSING_HOUR = 2000

# Range of valid work hours when a visitor can enter the restaurant.
VALID_HOURS = list(range(OPENING_HOUR, CLOSING_HOUR + 1))

# For how many hours visitors can enter the restaurant
NUM_OF_WORK_HOURS = CLOSING_HOUR - OPENING_HOUR + 1

# Number of visit days contributed by a single visitor will be limited to 3. All exceeding visits will be discarded.
COUNT_MAX_CONTRIBUTED_DAYS = 3

# Number of visit days contributed by a single visitor will be limited to 4. All exceeding visits will be discarded.
SUM_MAX_CONTRIBUTED_DAYS = 4

# Minimum amount of money we expect a visitor to spend on a single visit.
MIN_EUROS_SPENT = 0

# Maximum amount of money we expect a visitor to spend on a single visit.
MAX_EUROS_SPENT_1 = 50
MAX_EUROS_SPENT_2 = 65

LN_3 = math.log(3)


class RestaurantStatistics:
    def __init__(self, hours_filename, days_filename, epsilon=LN_3):

        # Store the name of the csvs for daily and weekly restaurant data
        self.hours_filename = hours_filename
        self.days_filename = days_filename

        # The privacy threshold, a number between 0 and 1
        self._epsilon = epsilon

        # The hourly and weekly data as pandas DataFrames
        self._hour_visits = pd.read_csv(self.hours_filename, sep=",")
        self._day_visits = pd.read_csv(self.days_filename, sep=",")

    def count_visits_per_hour(self) -> tuple:
        """Compute raw count of visits per hour of day and return two dictionaries 
        that map an hour to the number of visits in that hour. 
        
        The first dictionary is the count calculation without any differential privacy, while the second one uses the PyDP library for a private calculation
        """
        non_private_counts = self.get_non_private_counts_per_hour()
        private_counts = self.get_private_counts_per_hour()

        return non_private_counts, private_counts

    def count_visits_per_day(self) -> tuple:
        """Compute raw count of visits per day of week and return two dictionaries 
        that map a day to the number of visits in that day. 
        
        The first dictionary is the count calculation without any differential privacy, 
        while the second one uses the PyDP library for a private calculation
        """
        non_private_counts = self.get_non_private_counts_per_day()
        private_counts = self.get_private_counts_per_day()

        return non_private_counts, private_counts

    def sum_revenue_per_day(self) -> tuple:
        """Compute revenue per day for the whole week. 
        
        The first dictionary is the count calculation without any differential privacy, 
        while the second one uses the PyDP library for a private calculation
        """
        non_private_sum = self.get_non_private_sum_revenue()
        private_sum = self.get_private_sum_revenue()

        return non_private_sum, private_sum

    def sum_revenue_per_day_with_preaggregation(self) -> tuple:
        """Calculates revenue per day in the whole week while preagreggating the spending of each visitor before calculating the BoundedSum with PyDP.
        
        The first dictionary is the count calculation without any differential privacy, 
        while the second one uses the PyDP library for a private calculation
        """
        non_private_sum = self.get_non_private_sum_revenue()
        private_sum = self.get_private_sum_revenue_with_preaggregation()

        return non_private_sum, private_sum

    def get_non_private_counts_per_hour(self) -> dict:
        """Compute the number of visits per hour without any differential privacy. Return a dictionary mapping hours to number of visits"""
        hours_count = dict()

        # Parse times so its easy to check whether they are valid
        visits = self._hour_visits.copy()
        visits["Time entered"] = (
            pd.to_datetime(visits["Time entered"])
            .apply(lambda x: x.strftime(r"%H%M"))
            .astype(int)
        )

        # Only select the visits that happened during the valid hours
        valid_visits = visits[visits["Time entered"].isin(VALID_HOURS)]

        # Only count the hours without the minutes (12:00 and 12:30 both add 1 to the 12 count)
        valid_visits["Time entered"] = valid_visits["Time entered"].apply(
            lambda x: int(str(x)[:2]) if len(str(x)) == 4 else int(str(x)[:1])
        )

        for time in valid_visits["Time entered"].unique():
            hours_count[time] = valid_visits[valid_visits["Time entered"] == time][
                "Time entered"
            ].count()

        return hours_count

    def get_private_counts_per_hour(self, epsilon: float = None) -> dict:
        """Compute an anonymized (within a given threshold of epsilon) version of the number of visits per hour. Return a dictionary mapping hours to number of visits"""
        private_hours_count = dict()

        # Only count the hours without the minutes (12:00 and 12:30 both add 1 to the 12 count)
        visits = self._hour_visits.copy()
        visits["Time entered"] = (
            pd.to_datetime(visits["Time entered"])
            .apply(lambda x: x.strftime(r"%H"))
            .astype(int)
        )

        # Use the default epsilon value if it is not given as an argument
        if not epsilon:
            x = Count(epsilon=self._epsilon, dtype="int")
        else:
            x = Count(epsilon=epsilon, dtype="int")

        for time in visits["Time entered"].unique():
            # Can use either quick_result or a combination of add_entries() and result()
            private_hours_count[time] = x.quick_result(
                data=list(
                    visits[visits["Time entered"] == time]["Time entered"].astype(int)
                )
            )

        return private_hours_count

    def get_non_private_counts_per_day(self) -> dict:
        """Compute the number of visits per day without any differential privacy. Return a dictionary mapping days to number of visits"""
        day_counts = dict()

        for day in self._day_visits["Day"].unique():
            day_counts[day] = self._day_visits[self._day_visits["Day"] == day][
                "Day"
            ].count()

        return day_counts

    def get_private_counts_per_day(self, epsilon: float = None) -> dict:
        """Compute an anonymized (within a given threshold of epsilon) version of the number of visits per day. Return a dictionary mapping days to number of visits"""
        # Pre-process the data set: limit the number of days contributed by a visitor to COUNT_MAX_CONTRIBUTED_DAYS
        day_visits = bound_visits_per_week(self._day_visits, COUNT_MAX_CONTRIBUTED_DAYS)

        day_counts = dict()

        # Use the default epsilon value if it is not given as an argument
        if not epsilon:
            x = Count(
                epsilon=self._epsilon,
                l0_sensitivity=COUNT_MAX_CONTRIBUTED_DAYS,
                dtype="int",
            )
        else:
            x = Count(
                epsilon=epsilon, l0_sensitivity=COUNT_MAX_CONTRIBUTED_DAYS, dtype="int"
            )

        for day in day_visits["Day"].unique():
            # Can use either quick_result or a combination of add_entries() and result()
            day_counts[day] = x.quick_result(
                data=list(day_visits[day_visits["Day"] == day]["Day"])
            )

        return day_counts

    def get_non_private_sum_revenue(self) -> dict:
        """Compute the revenue per day of visits without any differential privacy. Return a dictionary mapping days to revenue"""
        day_revenue = dict()

        for day in self._day_visits["Day"].unique():
            day_revenue[day] = self._day_visits[self._day_visits["Day"] == day][
                "Money spent (euros)"
            ].sum()

        return day_revenue

    def get_private_sum_revenue(self, epsilon: float = None) -> dict:
        """Compute an anonymized (within a given threshold of epsilon) version of the revenue per day. Return a dictionary mapping days to revenue"""
        # Pre-process the data set: limit the number of days contributed by a visitor to SUM_MAX_CONTRIBUTED_DAYS
        day_visits = bound_visits_per_week(self._day_visits, SUM_MAX_CONTRIBUTED_DAYS)

        day_revenue = dict()

        # Use the default epsilon value if it is not given as an argument
        if not epsilon:
            x = BoundedSum(
                self._epsilon,
                MIN_EUROS_SPENT,
                MAX_EUROS_SPENT_1,
                l0_sensitivity=SUM_MAX_CONTRIBUTED_DAYS,
            )
        else:
            x = BoundedSum(
                epsilon,
                MIN_EUROS_SPENT,
                MAX_EUROS_SPENT_1,
                l0_sensitivity=SUM_MAX_CONTRIBUTED_DAYS,
            )

        for day in day_visits["Day"].unique():

            x.reset()
            # Can use either quick_result or a combination of add_entries() and result()
            x.add_entries(
                data=list(day_visits[day_visits["Day"] == day]["Money spent (euros)"])
            )
            day_revenue[day] = int(x.result())

        return day_revenue

    def get_private_sum_revenue_with_preaggregation(
        self, epsilon: float = None
    ) -> dict:
        """Compute an anonymized (within a given threshold of epsilon) version of the revenue per day. 
        
        Before performing the computation, 
        we pre-aggregate each visitor' spending for the day. Return a dictionary mapping days to revenue
        """

        # Pre-process the data set: limit the number of days contributed by a visitor to SUM_MAX_CONTRIBUTED_DAYS
        day_visits = bound_visits_per_week(self._day_visits, SUM_MAX_CONTRIBUTED_DAYS)

        day_revenue = dict()

        # Use the default epsilon value if it is not given as an argument
        if not epsilon:
            x = BoundedSum(
                self._epsilon,
                MIN_EUROS_SPENT,
                MAX_EUROS_SPENT_2,
                l0_sensitivity=SUM_MAX_CONTRIBUTED_DAYS,
            )
        else:
            x = BoundedSum(
                epsilon,
                MIN_EUROS_SPENT,
                MAX_EUROS_SPENT_2,
                l0_sensitivity=SUM_MAX_CONTRIBUTED_DAYS,
            )

        for day in day_visits["Day"].unique():
            # For each visitor, pre-aggregate their spending for the day.
            visits_on_day = day_visits[day_visits["Day"] == day][
                ["VisitorId", "Money spent (euros)"]
            ]
            visitor_to_spending = dict()

            for visitor in visits_on_day["VisitorId"].unique():
                visitor_to_spending[visitor] = visits_on_day[
                    visits_on_day["VisitorId"] == visitor
                ]["Money spent (euros)"].sum()

            spending = list(visitor_to_spending.values())

            x.reset()
            # Can use either quick_result or a combination of add_entries() and result()
            x.add_entries(data=spending)
            day_revenue[day] = int(x.result())

        return day_revenue


def bound_visits_per_week(df, limit):
    """Utility function to modify the input dataframes. 
    
    Makes sure that each visitor only contributes at most 3 visits per week,
    Returns an updated dataframe 
    """

    # Shuffle dataframe
    df = df.sample(frac=1)

    # Store results in new dataframe
    updated_df = pd.DataFrame(columns=df.columns)
    df_idx = 0

    # Keep track of visits per visitor and make sure it doesn't go above the limit
    # {visitor id: # of times it has visited the restaurant}
    id_to_visited = defaultdict(int)

    for index in df.index:
        if id_to_visited[df.loc[index]["VisitorId"]] < limit:
            updated_df.loc[df_idx] = df.loc[index]
            df_idx += 1
            id_to_visited[df.loc[index]["VisitorId"]] += 1

    return updated_df


if __name__ == "__main__":
    r = RestaurantStatistics(
        hours_filename="day_data.csv", days_filename="week_data.csv"
    )

    np_count_hour, p_count_hour = r.count_visits_per_hour()
    print("-----------------------------------")
    print("Visits per hour:")
    print("Non-private:", np_count_hour)
    print("Private:", p_count_hour)
    print("-----------------------------------")

    np_count_day, p_count_day = r.count_visits_per_day()
    print("Visits per day:")
    print("Non-private:", np_count_day)
    print("Private:", p_count_day)
    print("-----------------------------------")

    np_sum_day, p_sum_day = r.sum_revenue_per_day()
    print("Revenue per day:")
    print("Non-private:", np_sum_day)
    print("Private:", p_sum_day)
    print("-----------------------------------")

    np_sum_day_pa, p_sum_day_pa = r.sum_revenue_per_day_with_preaggregation()
    print("Revenue per day with preaggregation:")
    print("Non-private:", np_sum_day_pa)
    print("Private:", p_sum_day_pa)
    print("-----------------------------------")

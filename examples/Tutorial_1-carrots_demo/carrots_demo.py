#!/usr/bin/env python
# coding: utf-8

# 
# ## 1.1 Introduction to PyDP
# The PyDP package provides a Python API into [Google's Differential Privacy library](https://github.com/google/differential-privacy). This example uses the alpha 1.0.2 version of the package that has the following limitations:
# 
# 
# *   Supports Linux (Windows coming soon)
# *  Currently implements an algorithm to support computing private mean using a Laplace noise generation technique.
# * Supports only integer and floating point values
# 
# 

# # Example using Differential Privacy library
# 
# In this directory, we give a simple example of how to use the Python Differential
# Privacy library.
# 
# ## Zoo Animals
# 
# There are around 182 animals at Farmer Alex's zoo. Every day, Alex feeds
# the animals as many carrots as they desire. The animals record how many carrots
# they have eaten per day. For this particular day, the number of carrots eaten
# can be seen in `animals_and_carrots.csv`.
# 
# At the end of each day, Alex often asks aggregate questions about how many
# carrots everyone ate. For example, he wants to know how many carrots are eaten
# each day, so he knows how many to order the next day. The animals are fearful
# that Alex will use the data against their best interest. For example, Alex could
# get rid of the animals who eat the most carrots!
# 
# To protect themselves, the animals decide to use the Python Differential Privacy
# library to aggregate their data before reporting it to Alex. This way, the
# animals can control the risk that Alex will identify individuals' data while
# maintaining an adequate level of accuracy so that Alex can continue to run the
# zoo effectively.
# 

# In[ ]:


# Install the PyDP package
get_ipython().system(' pip install python-dp')


# In[1]:


import pydp as dp # by convention our package is to be imported as dp (for Differential Privacy!)
from pydp.algorithms.laplacian import BoundedSum, BoundedMean, BoundedStandardDeviation,BoundedVariance, Count, Max, Min, Median, Percentile
import pandas as pd
import statistics # for calculating mean without applying differential privacy
import numpy as np # for calculating percentile 


# In[29]:


print(dp.__version__)


# ## Data
# 
# Each row in `animals_and_carrots.csv` is composed of the name of an animal, and
# the number of carrots it has eaten, comma-separated.
# 

# In[2]:


# get carrots data from our public github repo
url = 'https://raw.githubusercontent.com/OpenMined/PyDP/dev/examples/Tutorial_1-carrots_demo/animals_and_carrots.csv'
df = pd.read_csv(url,sep=",", names=["animal", "carrots_eaten"])
df.head()


# Taking the mean of all the entries in a normal fashion without applying the DP library. This is the actual mean of all the records.

# ## Per-animal Privacy
# 
# Notice that each animal owns at most one row in the data. This means that we
# provide per-animal privacy. Suppose that some animal appears multiple times in
# the csv file. That animal would own more than one row in the data. In this case,
# using this DP library would not guarantee per-animal privacy! The animals would
# first have to pre-process their data in a way such that each animal doesn't own
# more than one row.
# 

# ## Mean

# In[3]:


# calculates mean without applying differential privacy
def mean_carrots() -> float:
        return statistics.mean(list(df["carrots_eaten"]))


# Private Mean uses Differential Privacy Library by Google to calculate the Mean. To preserve privacy, Laplacian mechanism is used.
# 
# The function takes the argument privacy_budget as input.
# 
# It is a number between 0 and 1, denoting privacy threshold
# 
# It measures the acceptable loss of privacy (with 0 meaning no loss is acceptable).
# 
# `BoundedMean.quick_result()` takes a List of integer/ float as an input and returns the mean of the list values.
# 

# In[4]:


# calculates mean applying differential privacy
def private_mean(privacy_budget: float) -> float:
        x = BoundedMean(privacy_budget, 1, 100)
        return x.quick_result(list(df["carrots_eaten"]))


# In[5]:


print("Mean: ", mean_carrots())
print("Private Mean: ", private_mean(0.8))


# As you can see, the value of the private mean varies compared to the mean calculated using non-private statistical methods.
# 
# This difference in value corresponds to the privacy that is actually preserved for individual records in it.

# ## Count

# Counts number of animals who ate more than 'limit' carrots without applying the DP library. This is the actual number of such animals.

# In[6]:


# Calculates number of animals who ate more than "limit" carrots without applying differential privacy.
def count_above(limit: int) -> int:
    return df[df.carrots_eaten > limit].count()[0]


# Private Count Above uses Differential Privacy Library by Google to calculate the number of rows with value above limit. To preserve privacy, Laplacian mechanism is used.
# 
# The function takes the argument privacy_budget as input.
# 
# It is a number between 0 and 1, denoting privacy threshold
# 
# It measures the acceptable loss of privacy (with 0 meaning no loss is acceptable).
# 
# The function also takes the limit as an argument.
# 
# `Count.quick_result()` takes a List of integer/ float as an input and returns the count of elements in the list. 

# In[7]:


# Calculates number of animals who ate more than "limit" carrots applying differential privacy.
def private_count_above(privacy_budget: float, limit: int) -> int:
    x = Count(privacy_budget, dtype="int")
    return x.quick_result(list(df[df.carrots_eaten > limit]["carrots_eaten"]))


# In[8]:


print("Above 70:\t" + str(count_above(70)))
print("private count above:\t" + str(private_count_above(1, 70)))


# As you can see, the value of Private Count Above varies compared to the Count calculated using normal Statistical methods.
# 
# This difference in values refers to that privacy is actually preserved for individual records in it.

# ## Max and Min

# Taking Max of all the entries in a normal fashion without Applying the DP library. This is the actual maximum of carrots eaten of all the records.

# In[9]:


# Function to return the maximum of the number of carrots eaten by any one animal without appyling differential privacy.
def maxi() -> int: # Named the function maxi because max is the name of a in-built fn
    return df.max()[1]


# In[10]:


# Function to return the maximum of the number of carrots eaten by any one animal without appyling differential privacy.
def mini() -> int: # Named the function mini because min is the name of a in-built fn
    return df.min()[1]


# Private Max and Min uses Differential Privacy Library by Google to calculate the maximum and minimum out of all the values. To preserve privacy, Laplacian mechanism is used.
# 
# The function takes the argument privacy_budget as input.
# 
# It is a number between 0 and 1, denoting privacy threshold
# 
# It measures the acceptable loss of privacy (with 0 meaning no loss is acceptable).
# 
# `Max.quick_result()` takes a List of integer/ float as an input and returns the list max value.
# 
# `Min.quick_result()` takes a List of integer/ float as an input and returns the list min value.

# In[11]:


# Function to return the maximum of the number of carrots eaten by any one animal appyling differential privacy.
def private_max(privacy_budget: float) -> int:
    # 0 and 150 are the upper and lower limits for the search bound.
    x = Max(privacy_budget, 0, 100, dtype="int")
    return x.quick_result(list(df["carrots_eaten"]))


# In[12]:


# Function to return the maximum of the number of carrots eaten by any one animal appyling differential privacy.
def private_min(privacy_budget: float) -> int:
    # 0 and 150 are the upper and lower limits for the search bound.
    x = Min(privacy_budget, 0, 100, dtype="int")
    return x.quick_result(list(df["carrots_eaten"]))


# In[13]:


print("Max:\t" + str(maxi()))
print("private max:\t" + str(private_max(1)))


# In[14]:


print("Min:\t" + str(mini()))
print("private min:\t" + str(private_min(1)))


# As you can see, the value of Private Max varies compared to the Max calculated using normal Statistical methods.
# 
# This difference in values refers to that privacy is actually preserved for individual records in it.

# ### Bounded Functions
# 
# Bounded functions use two additional paramters called Upper **(U)** and Lower **(L)**  limit parameters used
# to clamp (i.e., bound) each input.

# `BoundedSum()` function provides a differentially private sum, clamped between upper and lower values. 
# Bounds can be manually set or privately inferred.
# 
# Here, We set the lower and upper bounds to the minimum and maximum actual values in the carrots_eaten column. 

# In[15]:


# Defining the bounds
L= 0 # Minimum value in the table
U = 100 #Maximum value in the table


# ## Sum

# Taking Sum of all the entries in a normal fashion without Applying the DP library. This is the actual sum of carrots eaten by all the animals.

# In[16]:


# Function to calculate sum of carrots eaten without applying differential privacy.
def sum_carrots() -> int:
    return df.sum()[1]


# Private Sum uses Differential Privacy Library by Google to calculate the sum of all the values. To preserve privacy, Laplacian mechanism is used.
# 
# The function takes the argument privacy_budget as input.
# 
# It is a number between 0 and 1, denoting privacy threshold
# 
# It measures the acceptable loss of privacy (with 0 meaning no loss is acceptable).
# 
# `BoundedSum.quick_result()` takes a List of integer/ float as an input and returns the list sum.

# In[17]:


# Function to calculate sum of carrots eaten applying differential privacy.
def private_sum(privacy_budget: float) -> int:
    x = BoundedSum(privacy_budget,1,100, dtype="float")
    return x.quick_result(list(df["carrots_eaten"]))


# In[18]:


print("Sum:\t" + str(sum_carrots()))
print("Private Sum:\t" + str(private_sum(1)))


# As shown in the output, we see that the Sum calculated using bounded functions with differentially private algorithms as above varies compared to the values calculated using normal Statistical methods.
# 
# This difference in values refers to that privacy is actually preserved for individual records in it.

# ## Standard Deviation and Variance

# We now calculate the Standard Deviation and Variance stastically and privately for the same. 

# In[19]:


# Function to calculate bounded standard deviation of carrots eaten without applying differential privacy.
def standarddeviation_carrots() -> float:
    return statistics.stdev(list(df["carrots_eaten"]))


# In[20]:


# Function to calculate bounded standard deviation  of carrots eaten applying differential privacy.
def private_stddeviation(privacy_budget: float) -> int:
    x = BoundedStandardDeviation(epsilon=privacy_budget,lower_bound=L, upper_bound=U, l0_sensitivity=1,
            linf_sensitivity=100, dtype="float")
    return x.quick_result(list(df["carrots_eaten"]))


# In[21]:


print("Standard Deviation:\t" + str(standarddeviation_carrots()))
print("Private Standard Deviation:\t" + str(private_stddeviation(1)))


# In[22]:


# Function to calculate bounded variance  of carrots eaten without applying differential privacy.
def variance_carrots() -> float:
    return statistics.pvariance(list(df["carrots_eaten"]))


# In[23]:


# Function to calculate bounded variance of carrots eaten applying differential privacy.
def private_variance(privacy_budget: float) -> float:
    x = BoundedVariance(epsilon=privacy_budget,lower_bound=L, upper_bound=U, l0_sensitivity=1,linf_sensitivity=100, dtype="float")
    return x.quick_result(list(df["carrots_eaten"]))


# In[24]:


print("Variance:\t" + str(variance_carrots()))
print("Private Variance:\t" + str(private_variance(1)))


# As shown in the output, we see that the value of Standard Deviation and Variance calculated using bounded functions with differetnially private algorithms as above varies compared to the values calculated using normal Statistical methods.
# 
# This difference in values refers to that privacy is actually preserved for individual records in it.

# ## Percentile

# Here we try to find the value of the observation with the 95th percentile amongst the rest.
# So we set the value of the additional parameter `percentile` as 95

# In[25]:


percentile=95


# In[26]:


# Function to calculate percentile of carrots eaten without applying differential privacy.
def percentile_carrots(percentile : int) -> float:
    if percentile in range(0,101):
        return np.percentile(list(df["carrots_eaten"]),percentile)
    else:
        raise Exception("Sorry, no numbers below zero or above 100")


# In[27]:


# Function to calculate percentile of carrots eaten applying differential privacy.
def private_percentile(privacy_budget: float, percentile : int) -> float:
    x = Percentile(epsilon=privacy_budget,lower_bound=L, upper_bound=U,percentile=percentile/100, dtype="float")
    #print(percentile/100)
    return x.quick_result(list(df["carrots_eaten"]))


# In[28]:


print("Percentile:\t" + str(percentile_carrots(percentile)))
print("Private Percentile:\t" + str(private_percentile(1,percentile)))


# Once again, the value of percentile is differnt in both the cases due to the preserving of privacy of the individual records in the data.

# 
# 
# ## How to Run
# 
# ```python PyDP/example/carrots.py```
# 

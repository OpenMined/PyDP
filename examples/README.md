
## Curated list of Tutorials and Sample code for PyDP!


### Tutorials

#### Carrots Demo

This is the first example using the PyDP, about animals using the library to aggregate their data (about how many carrots they have eaten) before reporting it to their owner. More about it [here](carrots_demo/README.md).

#### Laplace Demo

This example shows how Laplace distribution is used to preserve the privacy in data by adding noise and scale it as per requirement before reporting it to someone else so that they do not get to be completely certain of the real result. Also it describes how well ε works with Laplace in setting up  differntial privacy by introducing the distribution equations and their respective plots.
More about it [here](laplace_demo/README.md)

#### Restaurant Demo

This example describes the statistics of a restaurant using it's daily and weekly data. It uses 2 Laplacian algorithms of PyDP library which are BoundedSum and Count to create anonymity in the resulting computed data. Count has been used for keeping the total number of visitors private while BoundedSum has been applied in total revenue of the restaurant in additon to the application of aggregationto preserve the privacy of the customers expenditure.
More about it [here](restaurant_demo/README.md)

### Example

* [Error Handling in PyDP](Sample_code/error_handing.py)

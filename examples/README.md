
## Curated list of Tutorials and Sample code for PyDP!


### Tutorials

#### Carrots Demo

This is the first example using the PyDP, about animals using the library to aggregate their data (about how many carrots they have eaten) before reporting it to their owner. More about it [here](Tutorial_1-carrots_demo/README.md).

#### Restaurant Demo

A restaurant owner would share business statistics with her visitors or potential clients, uses the PyDP library to preserve privacy of visitors while keeping track of number of visitors entering the restaurant and how much time and money they spend there. More about it [here](Tutorial_2-restaurant_demo/README.md).

#### Titanic Demo

This example uses the infamous Titanic dataset and finds what sorts of people were more likely to survive by finding demographic of people on the ship using differentially private statistical methods. More about it [here](Tutorial_3-Titanic_demo/titanic_notebook.ipynb).

#### Launch Demo

In this example, two copies of one database are created where they differ by one record. This is for demonstrating the general principle used by all differentially private algorithms to protect users from MIA(Membership Inference Attack). More about it [here](Tutorial_4-Launch_demo/DP_proof.ipynb).

#### Laplace Demo

This demo shows it is required to add noise to make data private. Laplace distribution makes it easy to satisfy ε-differential privacy by setting the b parameter to 1/ε. Hence, Laplace noise is used for making the data differentially private. More about it [here](laplace_demo/laplace.ipynb).

#### Naive Bayes Demo

This demo compares the results of scikit-learn's verses PyDP's Naive Bayes algorithm on various datasets. More about it [here](Naive_Bayes_Iris_demo/PyDP_Naive_Bayes.ipynb) and [here](Naive_Bayes_Iris_demo/PyDP_Naive_Bayes_Comparison.ipynb).

### Example

* [Error Handling in PyDP](Sample_code/error_handling.py)

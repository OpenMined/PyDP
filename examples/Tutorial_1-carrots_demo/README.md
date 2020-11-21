# Example using Differential Privacy library

In this directory, we give a simple example of how to use the Python Differential
Privacy library.

## Zoo Animals

There are around 182 animals at Farmer Alex's zoo. Every day, Alex feeds
the animals as many carrots as they desire. The animals record how many carrots
they have eaten per day. For this particular day, the number of carrots eaten
can be seen in `animals_and_carrots.csv`.

At the end of each day, Alex often asks aggregate questions about how many
carrots everyone ate. For example, he wants to know how many carrots are eaten
each day, so he knows how many to order the next day. The animals are fearful
that Alex will use the data against their best interest. For example, Alex could
get rid of the animals who eat the most carrots!

To protect themselves, the animals decide to use the Python Differential Privacy
library to aggregate their data before reporting it to Alex. This way, the
animals can control the risk that Alex will identify individuals' data while
maintaining an adequate level of accuracy so that Alex can continue to run the
zoo effectively.

## Data

Each row in `animals_and_carrots.csv` is composed of the name of an animal, and
the number of carrots it has eaten, comma-separated.

## Per-animal Privacy

Notice that each animal owns at most one row in the data. This means that we
provide per-animal privacy. Suppose that some animal appears multiple times in
the csv file. That animal would own more than one row in the data. In this case,
using this DP library would not guarantee per-animal privacy! The animals would
first have to pre-process their data in a way such that each animal doesn't own
more than one row.


## How to Run

```python PyDP/example/carrots.py```

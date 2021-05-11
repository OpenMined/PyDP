# pydp absolute
import pydp as dp

# Sample code to display error handling
x = dp.algorithms.laplacian.Max(1)
try:
    print(x.quick_result([2, 8]))
except RuntimeError as e:
    print("e")
except SystemError:
    print("system error")
else:
    print("i give up")

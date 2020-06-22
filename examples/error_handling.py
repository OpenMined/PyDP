import pydp as dp

# Sample code to display error handling
x = dp.Max(1)
try:
    print(x.result([2, 8], 1))
except RuntimeError as e:
    print("e")
except SystemError:
    print("system error")
else:
    print("i give up")

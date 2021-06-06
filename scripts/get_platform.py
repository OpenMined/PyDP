#!/bin/python3
import platform

p = platform.system().lower().replace("darwin", "macos")
print(p)

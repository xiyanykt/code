import random
import sympy

T = 10000
test = 100
n = T // test
W = 1000000
out = "5.in"

with open(out, "w") as f:
    f.write(f"2000\n")
    for _ in range(2000):
        f.write(f"{5}\n")
        f.write(f"999983 999983 999983 999979 999979\n")

from cyaron import *
import random

n = int(1e5)
m = 180000
W = 1000000000
lo, hi = 1, 1000000000

g = Graph.UDAG(n, m, direct=False, weight_limit=(lo, hi))
x = random.randint(-W, W)
print(f"{n} {m} {x}")
for _ in range(n):
    a = random.randint(-W, W)
    print(a, end=" " if _ < n - 1 else "\n")

for e in g.iterate_edges():
    u, v, w = e.start, e.end, e.weight
    print(f"{u} {v} {w}")

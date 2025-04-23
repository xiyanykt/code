from cyaron import *
import random

n = int(1e5)
q = int(1e5)
weight_limit_lo, weight_limit_hi = 1, (2**30) - 1
out = "5.in"

tree = Graph.tree(n, weight_limit=(weight_limit_lo, weight_limit_hi))

with open(out, "w") as f:
    f.write(f"{n}\n")
    for edge in tree.iterate_edges():
        u, v, w = edge.start, edge.end, edge.weight
        f.write(f"{u} {v} {w}\n")
    f.write(f"{q}\n")
    for _ in range(q):
        l, r = random.randint(1, n), random.randint(1, n)
        if l > r:
            l, r = r, l
        x = random.randint(1, n)
        f.write(f"{l} {r} {x}\n")

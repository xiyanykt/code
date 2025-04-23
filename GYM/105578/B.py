from math import *
from collections import defaultdict
import sys
import bisect

input = lambda: sys.stdin.readline().strip()
outs = []


def solve():
    n, m = map(int, input().split())

    c = [
        [
            ((j * n + 1) % (n * m)) * ((i * m + 1) % (n * m)) % (n * m)
            for j in range(1, m + 1)
        ]
        for i in range(1, n + 1)
    ]
    if (
        len(
            set(
                list(
                    [c[i - 1][j - 1] for i in range(1, n + 1) for j in range(1, m + 1)]
                )
            )
        )
        == n * m
    ):
        print("Yes")
        print(*[(i * m + 1) % (n * m) for i in range(1, n + 1)])
        print(*[(j * n + 1) % (n * m) for j in range(1, m + 1)])
    else:
        print("No")


t = int(input())
while t > 0:
    solve()
    t -= 1
print("\n".join(map(str, outs)))

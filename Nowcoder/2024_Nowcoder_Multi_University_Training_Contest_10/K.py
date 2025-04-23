from math import *
from collections import defaultdict
import sys
import bisect


def input(): return sys.stdin.readline().strip()


def solve():
    n = int(input())

    a = list(map(int, input().split()))

    ans = 0

    def work():
        nonlocal ans
        nonlocal a
        pos = bisect.bisect_left(a, 0)
        for i in range(pos+1):
            res = pos-bisect.bisect_left(a[i:pos], -i)
            lo, hi = pos, n
            while lo < hi:
                x = (lo+hi)//2
                if a[x-1] > -i+(n-x):
                    hi = x-1
                else:
                    lo = x
            ans = max(ans, res+lo-pos)

    work()
    a.reverse()
    a = [-x for x in a]
    work()
    print(ans)


t = int(input())
while t > 0:
    solve()
    t -= 1

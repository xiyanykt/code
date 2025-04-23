from math import *
import sys


def input(): return sys.stdin.readline().strip()


def solve():
    m, k, h = map(int, input().split())
    if h == 0:
        print(0)
        return

    if m == k:
        print(min(m, h))
        return

    if m > h:
        print(h)
        return

    def work(x):
        if x < m:
            return x >= h
        y = 1 + (x-m)//(m-k)
        return y*k + x >= h

    lo, hi = 0, 1000000000000
    while lo <= hi:
        mid = (lo+hi)//2
        if work(mid):
            hi = mid-1
        else:
            lo = mid+1
    print(hi+1)


t = int(input())
while t > 0:
    solve()
    t -= 1

from math import *
import sys


def input(): return sys.stdin.readline().strip()


def solve():
    n = int(input())
    a = list(map(int, input().split()))
    print(gcd(*a))


t = int(input())
while t > 0:
    solve()
    t -= 1

from math import gcd
import sys

input = lambda: sys.stdin.readline().rstrip()

n = int(input())

a = list(map(int, input().split()))

x = max(a)
y = gcd(*a)

l = x // y
l -= n

print('Alice') if l % 2 == 1 else print('Bob')

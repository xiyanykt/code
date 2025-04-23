import sys
import math

input = lambda: sys.stdin.readline().strip()
outs = []


def solve():
    x, y = map(int, input().split())
    outs.append(max(math.gcd(x, z) + math.gcd(z, y) for z in range(x + 1, y)))


t = int(input())
while t > 0:
    solve()
    t -= 1
print("\n".join(map(str, outs)))

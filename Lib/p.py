import sys

input = lambda: sys.stdin.readline().strip()
outs = []

def solve():
    

t = int(input())
while t > 0:
    solve()
    t -= 1
print("\n".join(map(str, outs)))
import sys

input = lambda: sys.stdin.readline().strip()
outs = []

def solve():
    n, m = map(int, input().split())
    cnt = 1
    dis = abs(n - m)
    prd = m
    for d in range(2, 301) :
        prd *= m
        if abs(prd - n) < dis:
            cnt = d
            dis = abs(prd - n)
    outs.append(cnt)


t = int(input())
while t > 0:
    solve()
    t -= 1
print("\n".join(map(str, outs)))
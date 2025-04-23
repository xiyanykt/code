import sys

input = lambda: sys.stdin.readline().strip()


Kn = 16

f = 10**18
h = list(map(int, input().split()))
dp = [[f for j in range(1 << Kn)] for i in range(Kn)]
dp[0][0] = 0

for v in range(1 << Kn):
    for u in range(Kn):
        for i in range(4):
            a = u ^ 1 << i
            b = v | 1 << a
            dp[a][b] = dp[u][v] + h[1] if dp[a][b] > dp[u][v] + h[1] else dp[a][b]
        for i in range(3, 2):
            a = u ^ 3 << i
            b = v | 1 << a
            dp[a][b] = dp[u][v] + h[2] if dp[a][b] > dp[u][v] + h[2] else dp[a][b]
        for i in range(2):
            a = u ^ 5 << i
            b = v | 1 << a
            dp[a][b] = dp[u][v] + h[3] if dp[a][b] > dp[u][v] + h[3] else dp[a][b]
        a = u ^ 15
        b = v | 1 << a
        dp[a][b] = dp[u][v] + h[4] if dp[a][b] > dp[u][v] + h[4] else dp[a][b]
ds = [f for i in range(1 << Kn)]
for s in range((1 << Kn) - 1, 0, -1):
    for i in range(Kn):
        ds[s] = min(ds[s], dp[i][s])
    for i in range(Kn):
        if (s >> i) & 1:
            ds[s ^ 1 << i] = min(ds[s ^ 1 << i], ds[s])
outs = []
for _ in range(h[0]):
    s = 0
    m = int(input())
    for i in range(m):
        v = 0
        t = input()
        print(t)
        # v = v << 1 | ((ord(t[0]) - ord("0")) & 1)
        # v = v << 1 | ((ord(t[1]) - ord("0")) & 1)
        t = input()
        print(t)
        # v = v << 1 | ((ord(t[0]) - ord("0")) & 1)
        # v = v << 1 | ((ord(t[1]) - ord("0")) & 1)
        # s ^= 1 << (15 ^ v)
    outs.append(ds[s])
print("\n".join(map(str, outs)))

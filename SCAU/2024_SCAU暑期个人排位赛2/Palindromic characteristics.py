# from math import gcd
import sys

input = lambda: sys.stdin.readline().rstrip()

s = input()
n = len(s)

dp = [[0] * n for _ in range(n)]

for i in range(n):
    dp[i][i] = 1

for len in range(2, n + 1):
    for i in range(n - len + 1):
        j = i + len - 1
        if s[i] == s[j] and (len == 2 or dp[i + 1][j - 1]):
            dp[i][j] = dp[i][i + len // 2 - 1] + 1

ans = [0] * (n + 1)
for i in range(n):
    for j in range(n):
        ans[dp[i][j]] += 1

for i in range(n, 0, -1):
    ans[i - 1] += ans[i]

print(*ans[1:])

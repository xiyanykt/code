#include<bits/stdc++.h>

using i64 = int64_t;

#define int long long

#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) (void)42
#endif

constexpr int N = 21;

int dp[N][10][2];

signed main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, m;
	while (true) {
		std::cin >> n >> m;

		if (n == 0 and m == 0) {
			break;
		}

		auto solve = [&](int x) {
			std::string s = std::to_string(x);
			int y = s.size();

			memset(dp, -1, sizeof(dp));

			auto dfs = [&](auto && self, int p, int pre, int c, int limits, int is) {
				if (p == y) {
					return (c);
				}
				if (not limits and is and dp[p][pre][c] != -1) {
					return dp[p][pre][c];
				}
				int res = 0;
				if (not is) {
					res += self(self, p + 1, pre, c, false, false);
				}
				int up = limits ? s[p] - '0' : 9;
				for (int d = 1 - is; d <= up; d += 1) {
					res += self(self, p + 1, d, c or ((pre == 6 and d == 2) or (d == 4)), limits and d == up, true);
				}
				if (not limits and is) {
					dp[p][pre][c] = res;
				}
				return res;
			};
			return dfs(dfs, 0, 0, 0, true, false);
		};

		std::cout << ((m - n + 1) - solve(m) + solve(n - 1)) << "\n";

	}

	return 0;
}
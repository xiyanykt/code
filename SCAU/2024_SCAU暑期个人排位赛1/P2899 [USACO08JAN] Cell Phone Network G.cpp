#include<bits/stdc++.h>

using i64 = int64_t;

#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) (void)42
#endif

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n;
	std::cin >> n;

	std::vector adj(n + 1, std::vector<int>());
	for (int i = 1; i <= n - 1; i += 1) {
		int u, v;
		std::cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	std::vector dp(3, std::vector<int>(n + 1));

	constexpr int inf = 1E9;

	auto dfs = [&](auto && self, int u, int par)->void {
		std::vector<int>p;
		dp[0][u] += 1;
		for (const auto & v : adj[u]) {
			if (v == par) {
				continue;
			}
			self(self, v, u);
			dp[0][u] += std::min({dp[0][v], dp[1][v], dp[2][v]});
			dp[2][u] += std::min(dp[0][v], dp[1][v]);
			dp[1][u] += dp[0][v];
			p.push_back(dp[1][v] - dp[0][v]);
		}
		if (p.empty()) {
			dp[1][u] = inf;
		} else{
			std::ranges::sort(p);
			for (const auto & c : p) {
				if (c < 0 and c != p.back()) {
					dp[1][u] += c;
				} else break;
			}
		}
	};

	dfs(dfs, 1, 0);

	std::cout << (std::min(dp[0][1], dp[1][1])) << "\n";

	return 0;
}
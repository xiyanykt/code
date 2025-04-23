#include<bits/stdc++.h>

using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;

#ifndef ONLINE_JUDGE
#include "algo\debug.hpp"
#else
#define debug(...) (void)42
#endif

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cout << std::fixed << std::setprecision(13);

	auto solve = [&]() {
		int n;
		std::cin >> n;

		std::vector adj(n + 1, std::vector<std::pair<int, int>>());
		for (int i = 1; i <= n - 1; i += 1) {
			int u, v, w;
			std::cin >> u >> v >> w;
			adj[u].push_back(std::pair(v, w));
			adj[v].push_back(std::pair(u, w));
		}

		std::vector<int>dep(n + 1);
		auto work = [&](auto && self, int u, int par)->void{
			dep[u] = dep[par] + 1;
			for (const auto & [v, w] : adj[u]) {
				if (v != par) {
					self(self, v, u);
				}
			}
		};
		work(work, 1, 0);

		std::vector<f64>dp(n + 1);
		for (int i = 1; i <= n; i += 1) {
			dp[i] = (dep[i] % 2) ? 1.0 : 0.0;
		}

		auto dfs = [&](auto && self, int u, int par, int cnt0, int cnt1)->void{
			if (adj[u].size() == 1 and u != 1) {
				dp[u] = 1.L * cnt0 / (cnt0 + cnt1);
			}
			for (const auto & [v, w] : adj[u]) {
				if (v == par) {
					continue;
				}
				self(self, v, u, cnt0 + (w == 0), cnt1 + (w == 1));
				if (dep[u] % 2 == 1) {
					dp[u] = std::min(dp[u], dp[v]);
				} else {
					dp[u] = std::max(dp[u], dp[v]);
				}
			}
			if (u != 1) {
				dp[u] = std::max(dp[u], 1.L * cnt0 / (cnt0 + cnt1));
			}
		};
		dfs(dfs, 1, 0, 0, 0);

		std::cout << (1 - dp[1]) << "\n";
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
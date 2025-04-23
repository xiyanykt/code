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

	auto solve = [&]() {
		int n;
		std::cin >> n;

		std::vector adj(n + 1, std::vector<int>());
		for (int i = 1; i <= n - 1; i += 1) {
			int u, v;
			std::cin >> u >> v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}

		std::vector<int>siz(n + 1);
		auto dfs = [&](auto && self, int u, int par)->void {
			for (const auto & v : adj[u]) {
				if (v == par) {
					continue;
				}
				self(self, v, u);
				siz[u] += siz[v];
			}
			if (not siz[u]) {
				siz[u] += 1;
			}
		};

		dfs(dfs, 1, 0);

		int q;
		std::cin >> q;
		while (q--) {
			int x, y;
			std::cin >> x >> y;
			std::cout << 1LL * siz[x]*siz[y] << "\n";
		}
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
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

	int n, m;
	std::cin >> n >> m;

	std::vector adj(n + 1, std::vector<int>());
	for (int i = 1; i <= m; i += 1) {
		int u, v;
		std::cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	int good = 0, ans = 0;
	std::vector<int>vis(n + 1);

	auto dfs = [&](auto && self, int u, int par)->void{
		vis[u] += 1;
		for (const auto & v : adj[u]) {
			if (v == par) {
				continue;
			}
			if (vis[v]) {
				good = 0;
				continue;
			}
			self(self, v, u);
		}
	};

	for (int i = 1; i <= n; i += 1) {
		if (not vis[i]) {
			good = 1;
			dfs(dfs, i, 0);
			ans += good;
		}
	}

	std::cout << ans << "\n";

	return 0;
}
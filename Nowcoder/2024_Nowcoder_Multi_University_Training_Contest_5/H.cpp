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

	int ans = 0;

	std::vector<int>vis(n + 1);
	for (int s = 1; s <= n; s += 1) {
		vis.assign(n + 1, 0);
		auto dfs = [&](auto && self, int x)->int{
			int res = 1;
			vis[x] += 1;
			for (const auto & y : adj[x]) {
				if (vis[y]) {
					continue;
				}
				for (const auto & v : adj[x]) {
					if (v != y) {
						vis[v] += 1;
					}
				}
				res = std::max(res, self(self, y) + 1);
				for (const auto & v : adj[x]) {
					if (v != y) {
						vis[v] -= 1;
					}
				}
			}
			vis[x] -= 1;
			return res;
		};
		ans = std::max(ans, dfs(dfs, s));
	}

	std::cout << ans << "\n";

	return 0;
}
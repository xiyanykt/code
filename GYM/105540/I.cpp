#include <bits/stdc++.h>

using i64 = long long;

void solve() {
	int n;
	std::cin >> n;

	std::vector<std::vector<int>> adj(n);
	for (int i = 1; i < n; i++) {
		int u, v;
		std::cin >> u >> v;
		u--, v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	if (n == 2) {
		std::cout << -1 << "\n";
		return;
	}

	int rt = -1;
	for (int i = 0; i < n; i++) {
		if (int(adj[i].size()) % 2 == 0) {
			rt = i;
		}
	}

	if (rt == -1) {
		std::cout << -1 << "\n";
		return;
	}

	std::vector<std::pair<int, int>> ans;
	auto dfs = [&](auto && self, int x, int p) -> std::vector<int> {
		std::vector<int> c;
		for (auto y : adj[x]) {
			if (y == p) {
				continue;
			}
			auto sc = self(self, y, x);
			c.insert(c.end(), sc.begin(), sc.end());
		}
		while (c.size() > 1) {
			int x = c.back();
			c.pop_back();
			int y = c.back();
			c.pop_back();
			ans.emplace_back(x, y);
		}
		if (c.empty()) {
			c.push_back(x);
		}
		return c;
	};
	dfs(dfs, rt, -1);

	std::cout << int(ans.size()) << "\n";
	for (auto [x, y] : ans) {
		std::cout << x + 1 << " " << y + 1 << "\n";
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int T;
	std::cin >> T;

	while (T--) {
		solve();
	}

	return 0;
}
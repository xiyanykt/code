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
		int n, m;
		std::cin >> n >> m;

		std::set<std::array<int, 2>>E;
		std::vector adj(n + 1, std::vector<int>());
		for (int i = 1; i <= m; i += 1) {
			int u, v;
			std::cin >> u >> v;
			adj[u].push_back(v);
			adj[v].push_back(u);
			if (u > v) {
				std::swap(u, v);
			}
			E.insert({u, v});
		}

		if (not std::none_of(adj.begin() + 1, adj.end(), [&](const auto & x) {return (int)x.size() == n - 1;})) {
			std::cout << "-1\n";
			return;
		}

		std::vector<int>c(n + 1, -1);
		std::vector rec(2, std::vector<int>());
		for (int i = 1; i <= n; i += 1) {
			if (c[i] != -1) {
				continue;
			}
			auto work = [&](auto && self, int u)->void{
				rec[c[u]].push_back(u);
				for (const auto & v : adj[u]) {
					if (c[v] == -1) {
						c[v] = c[u] ^ 1;
						self(self, v);
					}
				}
			};
			c[i] = 0;
			work(work, i);
		}

		bool done = false;
		for (int i = 0; i < (int)rec[0].size() and not done; i += 1) {
			for (int j = 0; j < (int)rec[1].size() and not done; j += 1) {
				int x = rec[0][i], y = rec[1][j];
				if (x > y) {
					std::swap(x, y);
				}
				if (not E.count({x, y})) {
					std::swap(rec[0][i], rec[0].back());
					std::swap(rec[1][j], rec[1][0]);
					done = true;
				}
			}
		}

		for (const auto & v : rec[0]) {
			std::cout << v << " ";
		}
		for (const auto & v : rec[1]) {
			std::cout << v << " ";
		}
		std::cout << "\n";
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
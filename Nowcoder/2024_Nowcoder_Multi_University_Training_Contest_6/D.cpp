#include <bits/stdc++.h>

using i64 = int64_t;

struct DSU {
	std::vector<int>par, siz;

	DSU() {}
	DSU(int n) {
		par.resize(n + 1);
		std::iota(par.begin() + 1, par.end(), 1);
		siz.assign(n + 1, 1);
	}

	int find(int x) {
		while (x != par[x]) {
			x = par[x] = par[par[x]];
		}
		return x;
	}

	bool same(int x, int y) {
		return find(x) == find(y);
	}

	bool merge(int x, int y) {
		x = find(x), y = find(y);
		if (x == y) {
			return false;
		}
		if (siz[x] < siz[y]) {
			std::swap(x, y);
		}
		siz[x] += siz[y];
		par[y] = x;
		return true;
	}

	int size(int x) {
		return siz[find(x)];
	}
};

struct EBCC {
	int n;
	std::vector<std::vector<int>> adj;
	std::vector<int> stk;
	std::vector<int> dfn, low, bel;
	int cur, cnt;

	EBCC() {}
	EBCC(int n) {
		this->n = n;
		adj.assign(n + 1, std::vector<int>());
		dfn.assign(n + 1, -1), bel.assign(n + 1, -1), low.resize(n + 1);
		stk.clear();
		cnt = cur = 0;
	}

	void addEdge(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	void dfs(int x, int p) {
		dfn[x] = low[x] = ++cur;
		stk.push_back(x);

		for (const auto& y : adj[x]) {
			if (y == p) {
				continue;
			}
			if (dfn[y] == -1) {
				dfs(y, x);
				low[x] = std::min(low[x], low[y]);
			} else if (bel[y] == -1 && dfn[y] < dfn[x]) {
				low[x] = std::min(low[x], dfn[y]);
			}
		}

		if (dfn[x] == low[x]) {
			int y;
			cnt++;
			do {
				y = stk.back();
				bel[y] = cnt;
				stk.pop_back();
			} while (y != x);
		}
	}

	std::vector<int> work() {
		// dfs(1, 0);
		// return bel;
		for (int i = 1; i <= n; i += 1) {
			if (bel[i] == -1) {
				dfs(i, 0);
			}
		}
		return bel;
	}

	struct Graph {
		int n;
		std::vector<std::pair<int, int>> edges;
		std::vector<int> siz;
		std::vector<int> cnte;
	};
	Graph compress() {
		Graph g;
		g.n = cnt, g.siz.resize(cnt + 1), g.cnte.resize(cnt + 1);
		for (int i = 1; i <= n; i++) {
			g.siz[bel[i]]++;
			for (const auto& j : adj[i]) {
				if (bel[i] < bel[j]) {
					g.edges.emplace_back(bel[i], bel[j]);
				} else if (i < j) {
					g.cnte[bel[i]]++;
				}
			}
		}
		return g;
	}
};

#ifndef ONLINE_JUDGE
#include "algo\debug.hpp"
#else
#define debug(...) (void)42
#endif

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, m;
	std::cin >> n >> m;

	EBCC b(n);

	std::vector<std::array<int, 2>>f, g;
	for (int i = 1; i <= m; i += 1) {
		int u, v;
		std::cin >> u >> v;
		std::string s;
		std::cin >> s;
		if (s == "Lun") {
			b.addEdge(u, v);
			f.push_back({u, v});
		} else {
			g.push_back({u, v});
		}
	}

	DSU dsu(n);
	std::vector<std::array<int, 2>>ans;

	auto bel = b.work();
	for (const auto & [u, v] : f) {
		if (bel[u] == bel[v]) {
			dsu.merge(u, v);
			ans.push_back({u, v});
		}
	}

	for (const auto & [u, v] : g) {
		if (dsu.merge(u, v)) {
			ans.push_back({u, v});
		}
	}

	// for (int i = 1; i <= n; i += 1) {
	// 	std::cerr << dsu.par[i] << " \n"[i == n];
	// }

	if (dsu.size(1) == n) {
		std::cout << "YES\n";
		std::cout << ans.size() << "\n";
		for (const auto & [u, v] : ans) {
			std::cout << u << " " << v << "\n";
		}
	} else {
		std::cout << "NO\n";
	}

	return 0;
}
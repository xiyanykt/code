#include <bits/stdc++.h>

using i64 = int64_t;

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
		dfs(1, 0);
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

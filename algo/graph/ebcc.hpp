struct EBCC {
	int n, cur, cnt;
	vector<vector<int>>adj;
	vector<int>low, dfn, bel, stk;

	EBCC() = default;

	EBCC(const int & n) {
		this->n = n;
		adj.assign(n + 1, {});
		dfn.assign(n + 1, -1);
		bel.assign(n + 1, -1);
		low.resize(n + 1);
		stk.clear();
		cur = cnt = 0;
	}

	void addEdge(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	void dfs(int u, int p) {
		dfn[u] = low[u] = ++cur;
		stk.emplace_back(u);
		for (const auto & v : adj[u]) {
			if (v == p) {
				continue;
			}
			if (dfn[v] == -1) {
				dfs(v, u);
				low[u] = min(low[u], low[v]);
			} else if (bel[v] == -1 && dfn[v] < dfn[u]) {
				low[u] = min(low[u], dfn[v]);
			}
		}

		if (dfn[u] == low[u]) {
			int v = -1;
			cnt += 1;
			do {
				v = stk.back();
				bel[v] = cnt;
				stk.pop_back();
			} while (u != v);
		}
	}

	vector<int>work() {
		dfs(1, 0);
		return bel;
	}

	struct Graph {
		int n;
		vector<pair<int, int>> edges;
		vector<int> siz;
		vector<int> cnte;
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
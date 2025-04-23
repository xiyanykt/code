#include<bits/stdc++.h>

using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;

#ifndef ONLINE_JUDGE
#include "algo\debug.hpp"
#else
#define debug(...) (void)42
#endif

struct HLD {
	int n;
	std::vector<std::vector<int>>adj;
	std::vector<int>dfn, siz, par, son, top, dep, seq;
	int cur;

	HLD() {}
	HLD(int n) {
		this->n = n;
		adj.assign(n + 1, std::vector<int>());
		dfn.resize(n + 1), par.resize(n + 1);
		son.resize(n + 1), siz.resize(n + 1);
		dep.resize(n + 1), top.resize(n + 1);
		seq.resize(n + 1);
		cur = 0;
	}

	void addEdge(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	void dfs(int u) {
		siz[u] += 1;
		dep[u] = dep[par[u]] + 1;
		for (const auto & v : adj[u]) {
			if (v == par[u]) {
				continue;
			}
			par[v] = u;
			dfs(v);
			siz[u] += siz[v];
			if (siz[v] > siz[son[u]]) {
				son[u] = v;
			}
		}
	}
	void dfs(int u, int h) {
		dfn[u] = ++cur;
		seq[cur] = u;
		top[u] = h;
		if (son[u]) {
			dfs(son[u], h);
		}
		for (const auto & v : adj[u]) {
			if (v == son[u] or v == par[u]) {
				continue;
			}
			dfs(v, v);
		}
	}

	void work(int s = 1) {
		dfs(s);
		dfs(s, s);
	}

	int lca(int u, int v) {
		while (top[u] != top[v]) {
			if (dep[top[u]] < dep[top[v]]) {
				std::swap(u, v);
			}
			u = par[top[u]];
		}
		return dep[u] < dep[v] ? u : v;
	}

	int lca(int u, int v, int root) {
		return lca(u, v) ^ lca(u, root) ^ lca(v, root);
	}

	int dist(int u, int v) {
		return (dep[u] + dep[v] - 2 * dep[lca(u, v)]);
	}

	int jump(int u, int k) {
		if (dep[u] <= k) {
			return -1;
		}
		int d = dep[u] - k;
		while (dep[top[u]] > d) {
			u = par[top[u]];
		}
		return seq[dfn[u] + d - dep[u]];
	}

	int left(int u) {
		return dfn[u];
	}

	int right(int u) {
		return dfn[u] + siz[u] - 1;
	}
};

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cout << std::fixed << std::setprecision(13);

	int n, q;
	std::cin >> n >> q;

	HLD hld(n);
	for (int i = 1; i <= n - 1; i += 1) {
		int a, b;
		std::cin >> a >> b;
		hld.addEdge(a, b);
	}

	hld.work();

	while (q--) {
		int a, b;
		std::cin >> a >> b;
		int l = hld.dist(a, b);
		std::cout << ((l % 2) ? "Road\n" : "Town\n");
	}

	return 0;
}
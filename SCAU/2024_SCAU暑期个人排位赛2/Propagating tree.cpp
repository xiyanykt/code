#include<bits/stdc++.h>

using i64 = int64_t;

template<typename T>
struct Fenwick {
	int n;
	std::vector<T>a;

	Fenwick(const int n = 0): n(n), a(n + 1, T()) {}

	void add(int p, const T& x) {
		while (p <= n) {
			a[p] += x;
			p += p & -p;
		}
	}

	T sum(int p) {
		T res = T();
		while (p) {
			res += a[p];
			p -= p & -p;
		}
		return res;
	}

	T rangeSum(int l, int r) {
		return sum(r) - sum(l - 1);
	}
};

#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) (void)42
#endif

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, q;
	std::cin >> n >> q;

	std::vector<int>w(n + 1);
	for (int i = 1; i <= n; i += 1) {
		std::cin >> w[i];
	}

	std::vector adj(n + 1, std::vector<int>());
	for (int i = 1; i <= n - 1; i += 1) {
		int u, v;
		std::cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	std::vector<int>dep(n + 1), siz(n + 1), dfn(n + 1);
	int lo = 0;
	auto work = [&](auto && self, int u, int par)->void {
		siz[u] += 1;
		dep[u] = dep[par] + 1;
		dfn[u] = ++lo;
		for (const auto & v : adj[u]) {
			if (v == par) {
				continue;
			}
			self(self, v, u);
			siz[u] += siz[v];
		}
	};

	work(work, 1, 0);

	Fenwick<i64>fen(n);
	for (int i = 1; i <= n; i += 1) {
		fen.add(dfn[i], w[i] * ((dep[i] & 1) ? 1 : -1));
		fen.add(dfn[i] + 1, -w[i] * ((dep[i] & 1) ? 1 : -1));
	}

	while (q--) {
		int op;
		std::cin >> op;
		if (op == 1) {
			int u, val;
			std::cin >> u >> val;
			fen.add(dfn[u], val * (dep[u] % 2 ? 1 : -1));
			fen.add(dfn[u] + siz[u], val * (dep[u] % 2 ? -1 : 1));
		} else {
			int v;
			std::cin >> v;
			std::cout << (fen.sum(dfn[v]) * (dep[v] % 2 ? 1 : -1)) << "\n";
		}
	}

	return 0;
}
#include<bits/stdc++.h>

using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;

#ifndef ONLINE_JUDGE
#include "algo\debug.hpp"
#else
#define debug(...) (void)42
#endif

struct SCC {
	int n;
	std::vector<std::vector<int>>adj;
	std::vector<int>dfn, low, bel;
	std::vector<int>stk;
	int cnt, cur;

	SCC () {}

	SCC(int n) {
		this->n = n;
		adj.assign(n + 1, std::vector<int>());
		dfn.assign(n + 1, -1), bel.assign(n + 1, -1), low.resize(n + 1);
		cur = cnt = 0;
	}

	void addEdge(int u, int v) {
		adj[u].emplace_back(v);
	}

	void tarjan(int x) {
		dfn[x] = low[x] = ++cur;
		stk.emplace_back(x);

		for (const auto & y : adj[x]) {
			if (dfn[y] == -1) {
				tarjan(y);
				low[x] = std::min(low[x], low[y]);
			} else if (bel[y] == -1) {
				low[x] = std::min(low[x], dfn[y]);
			}
		}

		if (dfn[x] == low[x]) {
			cnt += 1;
			int y;
			do {
				y = stk.back(), stk.pop_back();
				bel[y] = cnt;
			} while (y != x);
		}
	}

	std::vector<int> work() {
		for (int j = 1; j <= n; j += 1) {
			if (dfn[j] == -1) {
				tarjan(j);
			}
		}
		return bel;
	}

};

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cout << std::fixed << std::setprecision(13);

	int n;
	std::cin >> n;

	SCC scc(n);
	for (int i = 1; i <= n; i += 1) {
		int a;
		std::cin >> a;
		scc.addEdge(i, a);
	}

	auto bel = scc.work();

	std::map<int, int>rec;
	for (int i = 1; i <= n; i += 1) {
		rec[bel[i]] += 1;
	}

	int ans = 1145141;

	for (const auto & [x, v] : rec) {
		if (v == 1) {
			continue;
		}
		ans = std::min(ans, v);
	}

	std::cout << ans << "\n";
	return 0;
}

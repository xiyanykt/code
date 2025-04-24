#include<bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f64 = long double;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

#ifndef ONLINE_JUDGE
#include "algo/debug.hpp"
#else
#define debug(...) (void)13
#endif

template<class T>
constexpr bool chmax (T& x, T y) {
	if (y > x) {
		x = y;
		return true;
	}
	return false;
}

template<class T>
constexpr bool chmin (T& x, T y) {
	if (y < x) {
		x = y;
		return true;
	}
	return false;
}

constexpr i64 inf = 1E9;
template <class T>
struct MaxFlow {
	struct edge {
		int to;
		T cap;
		edge(const int& to, const T& cap): to{to}, cap{cap} {}
	};

	int n;
	std::vector<edge>e;
	std::vector<std::vector<int>>adj;
	std::vector<int>cur, h;

	MaxFlow() {}
	MaxFlow(int n): n{n}, e{}, adj(n), cur(n), h(n) {}

	bool bfs(int s, int t) {
		h.assign(n, -1);
		std::queue<int>q;
		h[s] = 0;
		q.push(s);
		while (!q.empty()) {
			auto u = q.front();
			q.pop();
			for (int i : adj[u]) {
				auto [v, c] = e[i];
				if (c > 0 && h[v] == -1) {
					h[v] = h[u] + 1;
					if (v == t) {
						return true;
					}
					q.push(v);
				}
			}
		}
		return false;
	}

	T dfs(int u, int t, T f) {
		if (u == t) {
			return f;
		}
		auto r = f;
		for (int& i = cur[u]; i < int(adj[u].size()); i += 1) {
			int j = adj[u][i];
			auto [v, c] = e[j];
			if (c > 0 && h[v] == h[u] + 1) {
				auto a = dfs(v, t, std::min(r, c));
				e[j].cap -= a;
				e[j ^ 1].cap += a;
				r -= a;
				if (r == 0) {
					return f;
				}
			}
		}
		return f - r;
	}

	void addEdge(int u, int v, T cap) {
		adj[u].push_back(int(e.size()));
		e.emplace_back(v, cap);
		adj[v].push_back(int(e.size()));
		e.emplace_back(u, 0);
	}

	T flow(int s, int t) {
		T ans = 0;
		while (bfs(s, t)) {
			cur.assign(n, 0);
			ans += dfs(s, t, std::numeric_limits<T>::max());
		}
		return ans;
	}

	std::vector<bool>mincut() {
		std::vector<bool>c(n);
		for (int i = 0; i < n; i += 1) {
			c[i] = (h[i] != -1);
		}
		return c;
	}

	struct Edge {
		int from;
		int to;
		T cap;
		T flow;
		Edge() {}
	};
	std::vector<Edge>edges() {
		std::vector<Edge>a;
		for (int i = 0; i < e.size(); i += 2) {
			Edge x;
			x.from = e[i + 1].to;
			x.to = e[i].to;
			x.cap = e[i].cap + e[i + 1].cap;
			x.flow = e[i + 1].cap;
			a.push_back(x);
		}
		return a;
	}
};

void solve () {
	
}

auto main() ->int {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
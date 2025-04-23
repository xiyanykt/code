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
#define debug(...) (void)42
#endif

template<class T>
constexpr bool chmax(T& x, T y) {
	if (y > x) {
		x = y;
		return true;
	}
	return false;
}

template<class T>
constexpr bool chmin(T& x, T y) {
	if (y < x) {
		x = y;
		return true;
	}
	return false;
}

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout << std::fixed << std::setprecision(13);

	auto solve = [&]() {
		int n;
		std::cin >> n;

		std::vector adj(n + 1, std::vector<int>());
		for (int i = 1; i <= n - 1; i += 1) {
			int u, v;
			std::cin >> u >> v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}

		int t = 0;
		std::vector<int>a(n + 1);
		for (int u = 1; u <= n; u += 1) {
			if (adj[u].size() == 1) {
				a[u] = 1;
				a[adj[u][0]] = 2;
				t = u;
				break;
			}
		}

		std::vector<int>pool;
		for (int x = 4; x <= 2 * n; x += 2) {
			pool.push_back(x);
		}
		int l = 0, r = pool.size() - 1;
		std::vector<int>col(n + 1);
		col[t] = col[adj[t][0]] = 1;
		auto dfs = [&](this auto && dfs, int u, int par) ->void {
			for (const auto & v : adj[u]) {
				if (v == par) {
					continue;
				}
				if (!a[v]) {
					if (col[u]) {
						a[v] = pool[r--];
					} else {
						a[v] = pool[l++];
					}
					col[v] = col[u] ^ 1;
				}
				dfs(v, u);
			}
		};

		dfs(t, 0);
		for (int i = 1; i <= n; i += 1) {
			std::cout << a[i] << " \n"[i == n];
		}
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
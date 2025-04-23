#include<bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f64 = long double;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

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

	auto solve = [&]() {
		int n;
		std::cin >> n;

		std::vector<int>r(n + 1);
		for (int i = 1; i <= n; i += 1) {
			std::cin >> r[i];
		}

		std::vector<std::vector<int>>adj(n + 1);
		for (int i = 1; i <= n; i += 1) {
			adj[r[i]].push_back(i);
		}

		std::vector<int>vis(n + 1), cyc(n + 1);
		for (int i = 1; i <= n; i += 1) {
			if (vis[i]) {
				continue;
			}
			int j = i;
			std::vector<int>d;
			while (!vis[j]) {
				d.push_back(j);
				vis[j] = 1;
				j = r[j];
			}
			for (auto it = std::ranges::find(d, j); it != d.end(); it = std::next(it)) {
				cyc[*it] = 1;
			}
		}

		int ans = 2;
		std::vector<int>siz(n + 1), dep(n + 1);
		auto dfs = [&](auto && dfs, int u) ->void {
			siz[u] += 1;
			for (const auto & v : adj[u]) {
				if (cyc[v]) {
					continue;
				}
				dep[v] = dep[u] + 1;
				dfs(dfs, v);
				siz[u] += siz[v];
			}
			if (!cyc[u]) {
				chmax(ans, dep[u] + siz[u] + 1);
			}
		};
		for (const int & u : std::views::iota(1, n + 1)) {
			if (cyc[u]) {
				dfs(dfs, u);
			}
		}
		std::cout << ans << '\n';
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
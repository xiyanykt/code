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

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout << std::fixed << std::setprecision(13);

	auto solve = [&]() {
		int n;
		std::cin >> n;

		std::vector<int>a(n + 1);
		for (int i = 1; i <= n; i += 1) {
			std::cin >> a[i];
		}

		DSU dsu(n);
		std::vector<int>t(n + 1);
		auto merge = [&](int l, int r) {
			int mid = (l + r) >> 1;
			int i = l, j = mid + 1, c = l, d = 0;
			while (i <= mid and j <= r) {
				if (a[i] <= a[j]) {
					t[c++] = a[i++];
				} else {
					if (not d) {
						for (int u = i; u < mid; u += 1) {
							dsu.merge(u, u + 1);
						}
					}
					d += 1;
					dsu.merge(i, j);
					t[c++] = a[j++];
				}
			}
			while (i <= mid) {
				t[c++] = a[i++];
			}
			while (j <= r) {
				t[c++] = a[j++];
			}
			std::copy(t.begin() + l, t.begin() + r + 1, a.begin() + l);
		};

		auto dfs = [&](this auto && dfs, int l, int r) {
			if (l == r) {
				return;
			}
			int mid = (l + r) >> 1;
			dfs(l, mid);
			dfs(mid + 1, r);
			merge(l, r);
		};
		dfs(1, n);

		auto w = a;
		for (int i = 1; i <= n; i += 1) {
			chmax(w[dsu.find(i)], w[i]);
		}

		for (int i = 1; i <= n; i += 1) {
			std::cout << w[dsu.find(i)] << " \n"[i == n];
		}
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
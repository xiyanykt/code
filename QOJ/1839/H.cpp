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
		int n, k;
		std::cin >> n >> k;

		std::vector<int>l(k + 1), r(k + 1);
		for (int i = 1; i <= k; i += 1) {
			std::cin >> l[i] >> r[i];
		}

		std::vector<int>ord(k + 1);
		std::iota(ord.begin() + 1, ord.end(), 1);
		std::ranges::stable_sort(ord, {}, [&](const int &i) {
			return r[i] - l[i];
		});

		if (n == 1) {
			std::cout << 0 << '\n';
			return ;
		}

		if (r[ord.back()] - l[ord.back()] + 1 == 1) {
			std::cout << "IMPOSSIBLE\n";
			return ;
		}

		std::vector<int>par(n + 1);
		for (int u = l[ord.back()] + 1; u <= r[ord.back()]; u += 1) {
			par[u] = u - 1;
		}

		int j = 1;
		int cur = 1;
		for (int h = r[ord.back()] - 1; h >= l[ord.back()]; h -= 1) {
			int rec = 0;
			while (j <= k - 1 && r[ord[j]] - l[ord[j]] + 1 <= cur) {
				par[l[ord[j]]] = h;
				for (int v = l[ord[j]] + 1; v <= r[ord[j]]; v += 1) {
					par[v] = v - 1;
				}
				rec += r[ord[j]] - l[ord[j]] + 1;
				j += 1;
			}
			cur += rec + 1;
		}

		if (j <= k - 1) {
			std::cout << "IMPOSSIBLE\n";
			return ;
		}

		for (int u = 1; u <= n; u += 1) {
			std::cout << par[u] << " \n"[u == n];
		}
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}

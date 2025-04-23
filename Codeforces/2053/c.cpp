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

auto main() ->int {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	auto solve = [&]() {
		int n, k;
		std::cin >> n >> k;
	
		auto dfs = [&](auto&& dfs, int l, int r) -> std::pair<i64, i64> {
			if (r - l + 1 < k) {
				return {0, 0};
			}
			if ((r - l + 1) % 2 == 0) {
				i64 mid = (l + r) >> 1;
				auto [x, y] = dfs(dfs, l, mid);
				return {2 * x, y + x * mid + y};
			} else {
				i64 mid = (l + r) >> 1;
				auto [x, y] = dfs(dfs, l, mid - 1);
				return {2 * x + 1, mid + y + x * mid + y};
			}
		};

		std::cout << dfs(dfs, 1, n).second << '\n';
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
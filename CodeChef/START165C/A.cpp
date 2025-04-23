#include<bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f64 = long double;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

#include"W:\v\algo\debug.hpp"

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
		int n, m, k;
		std::cin >> n >> m >> k;

		int r = 1E9;
		for (int x = 1; x <= n; x += 1) {
			for (int y = 1; y <= m; y += 1) {
				chmin(r, std::abs(k - 2 * (x + y)));
			}
		}

		std::cout << r << '\n';
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
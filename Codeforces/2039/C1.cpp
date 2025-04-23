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

	// constexpr int Kn = 100;
	// for (int x = 1; x <= Kn; x += 1) {
	// 	for (int y = x + 1; y <= Kn; y += 1) {
	// 		int t = x ^ y;
	// 		// if (x % t == 0 || y % t == 0) {
	// 		// debug(x, y, t);
	// 		// }
	// 		if (y % t == 0) {
	// 			debug(x, y, t);
	// 		}
	// 	}
	// }

	auto solve = [&]() {
		int x;
		i64 m;
		std::cin >> x >> m;

		// i64 res = 0;
		// for (i64 y = 1; y <= m; y += 1) {
		// 	if (y == x) {
		// 		continue;
		// 	}
		// 	i64 t = y ^ x;
		// 	res += (x % t == 0 || y % t == 0);
		// }
		// std::cout << res << '\n';

		int res = 0;
		for (int y = 1; y <= std::min(m, 4ll * x); y += 1) {
			if (y == x) {
				continue;
			}
			int t = x ^ y;
			if (x % t == 0 || y % t == 0) {
				res += 1;
			}
		}
		std::cout << res << '\n';
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
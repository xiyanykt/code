#include<bits/stdc++.h>

using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128_t;
using f128 = __float128;

#ifndef ONLINE_JUDGE
#include "algo/debug.hpp"
#else
#define debug(...) (void)42
#endif

template<class T>
constexpr void chmax(T& x, T y) {
	if (y > x) {
		x = y;
	}
}

template<class T>
constexpr void chmin(T& x, T y) {
	if (y < x) {
		x = y;
	}
}

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout << std::fixed << std::setprecision(13);

	auto solve = [&]() {
		int n, k;
		std::cin >> n >> k;

		constexpr i64 inf = 1E13;
		std::vector<i64>dp(k + 1, inf );
		dp[0] = 0;
		for (int i = 1; i <= n; i += 1) {
			std::array<int, 4>f {};
			std::cin >> f[0] >> f[1] >> f[2] >> f[3];
			for (int x = std::min(k, 4 * i); x >= 0; x -= 1) {
				for (int j = 3; j >= 0; j -= 1) {
					if (x - j - 1 >= 0) {
						chmin(dp[x], dp[x - j - 1] + f[j]);
					}
				}
			}
		}
		std::cout << dp[k] << '\n';
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
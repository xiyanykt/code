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

	std::array<int, 2>f {};
	for (int x = 0; x <= 1; x += 1) {
		for (const auto & a : {0, 1}) {
			for (const auto & b : {0, 1}) {
				for (const auto& c : {0, 1}) {
					for (const auto & d : {0, 1}) {
						if ((((a & b)^c) | d) == x) {
							f[x] += 1;
						}
					}
				}
			}
		}
	}

	auto solve = [&]() {
		int n, k;
		std::cin >> n >> k;

		i64 ans = 1;
		for (int i = 0; i < k; i += 1) {
			ans *= f[n >> i & 1];
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
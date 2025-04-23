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

	int n;
	std::cin >> n;

	i64 cur = 1500;
	for (int i = 1; i <= n; i += 1) {
		int x;
		std::cin >> x;
		cur += x;
		if (cur >= 4000) {
			std::cout << i << '\n';
			return 0;
		}
	}

	std::cout << -1 << '\n';

	return 0;
}
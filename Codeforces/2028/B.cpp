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
		i64 n, b, c;
		std::cin >> n >> b >> c;

		if (c >= n) {
			std::cout << n << '\n';
			return ;
		}

		if (b == 0) {
			if (n - c >= 3) {
				std::cout << -1 << '\n';
			} else {
				std::cout << n - 1 << '\n';
			}
			return ;
		}

		std::cout << (n - *std::ranges::partition_point(std::ranges::iota_view(1ll, n + 1), [&](i64 i) {
			return i128(i - 1) * b + c <= n - 1;
		}) + 1) << '\n';
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
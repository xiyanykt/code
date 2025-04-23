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

// 0 -> 0
// 1 -> 1
// 2 -> 4

// 3 -> 9

// add 6

// 4 -> 16

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout << std::fixed << std::setprecision(13);

	auto solve = [&]() {
		std::string s;
		std::cin >> s;

		int a = 0;
		int d = 0, e = 0;
		for (const auto & c : s) {
			a += c - '0';
			d += c == '3';
			e += c == '2';
		}

		for (int i = 0; i <= std::min(e, 8); i += 1) {
			for (int j = 0; j <= std::min(d, 8); j += 1) {
				if ((a + (i * 2) + (j * 6)) % 9 == 0) {
					debug(a, i, j);
					std::cout << "YES\n";
					return ;
				}
			}
		}
		std::cout << "NO\n";
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
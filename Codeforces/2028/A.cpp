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
		int n, a, b;
		std::cin >> n >> a >> b;

		std::string s;
		std::cin >> s;
		s += s;
		s += s;
		s += s;
		s += s;
		s += s;
		s += s;
		s += s;
		s += s;
		s += s;
		s += s;
		s += s;
		s += s;
		s += s;

		int x = 0, y = 0;
		for (const auto & c : s) {
			if (a == x and b == y) {
				std::cout << "YES\n";
				return ;
			}
			if (c == 'W') {
				x -= 1;
			} else if (c == 'N') {
				y += 1;
			} else if (c == 'S') {
				y -= 1;
			} else {
				x += 1;
			}
		}

		if (a == x and b == y) {
			std::cout << "YES\n";
			return ;
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
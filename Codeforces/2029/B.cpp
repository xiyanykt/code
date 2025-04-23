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
		int n;
		std::cin >> n;

		std::string s, t;
		std::cin >> s >> t;

		if (n == 2) {
			std::cout << (s[0] == s[1] ? "NO\n" : "YES\n");
			return ;
		}

		int cnt0 = std::ranges::count(s, '0');
		int cnt1 = std::ranges::count(s, '1');
		for (int i = 0; i < n - 1; i += 1) {
			if (cnt0 == 0 or cnt1 == 0) {
				std::cout << "NO\n";
				return ;
			}
			t[i] == '0' ? cnt1 -= 1 : cnt0 -= 1;
		}
		std::cout << "YES\n";
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
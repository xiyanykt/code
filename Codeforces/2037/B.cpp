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
		int k;
		std::cin >> k;

		int t = k - 2;
		std::set<int>rec;
		for (int i = 1; i <= k; i += 1) {
			int x;
			std::cin >> x;
			rec.insert(x);
		}

		for (const auto & x : rec) {
			if (t % x == 0 and rec.contains(t / x)) {
				std::cout << x << ' ' << t / x << '\n';
				return ;
			}
		}
		assert(false);
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
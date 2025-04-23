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

	constexpr int Kn = 1E7;
	int cur = 1;
	std::vector<int>f(Kn + 1);
	for (int r = 1, l = 1; r <= Kn; r *= 2, r += 2) {
		debug(l, r);
		for (int j = l; j <= r; j += 1) {
			f[j] = cur;
		}
		cur += 1;
		l = r + 1;
	}

	auto solve = [&]() {
		int n;
		std::cin >> n;

		std::cout << f[n] << '\n';
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
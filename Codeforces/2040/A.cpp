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
		int n, k;
		std::cin >> n >> k;

		std::vector<int>a(n + 1);
		for (int i = 1; i <= n; i += 1) {
			std::cin >> a[i];
		}

		for (int i = 1; i <= n; i += 1) {
			int ok = 1;
			for (int j = 1; j <= n; j += 1) {
				if (i == j) {
					continue;
				}
				ok &= (std::abs(a[i] - a[j]) % k != 0);
			}
			if (ok) {
				std::cout << "Yes\n";
				std::cout << i << '\n';
				return ;
			}
		}
		std::cout << "No\n";
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
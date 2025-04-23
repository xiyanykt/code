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

		int s = 0;
		std::vector<int>a (n + 1);
		for (int i = 1; i <= n; i += 1) {
			std::cin >> a[i];
			s += a[i];
		}

		std::sort(a.begin() + 1, a.end(), std::greater());
		int x = 1E9;
		if (s < k) {
			x = k - s;
		} else {
			s = 0;
			for (int l = 1; l <= n; l += 1) {
				if (s + a[l] > k) {
					break;
				}
				s += a[l];
			}
			chmin(x, k - s);
		}

		chmin(x, k - a[1]);

		std::cout << x << '\n';
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
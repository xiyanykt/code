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

constexpr int Kn = 1E5;
int cap[Kn + 1];

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	for (int x = 2; x <= Kn; x += 1) {
		int y = x;
		for (int j = 2; j * j <= y; j += 1) {
			while (y % j == 0) {
				y /= j;
				cap[x] += 1;
			}
		}
		if (y > 1) {
			cap[x] += 1;
		}
	}

	auto solve = [&]() {
		int n, m;
		std::cin >> n >> m;

		std::vector<int>s(m + 1);
		for (int i = 1; i <= m; i += 1) {
			std::cin >> s[i];
		}

		std::reverse(s.begin() + 1, s.end());

		if (*std::max_element(cap + 1, cap + n + 1) >= m) {
			std::cout << -1 << '\n';
		} else {
			for (int i = 1; i <= n; i += 1) {
				std::cout << s[cap[i] + 1] << " \n"[i == n];
			}
		}
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
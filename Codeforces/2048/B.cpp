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

		int cur = 1;
		std::vector<int>p(n + 1);
		for (int i = k; i <= n; i += k) {
			p[i] = cur ++;
		}
		for (int i = 1; i <= n; i += 1) {
			if (p[i] == 0) {
				p[i] = cur ++;
			}
		}

		for (int i = 1; i <= n; i += 1) {
			std::cout << p[i] << ' ';
		}
		std::cout << '\n';
	};

	auto bf = [&]() {
		int n, k;
		std::cin >> n >> k;

		int x = 1E9;
		std::vector<int>p(n);
		std::ranges::iota(p, 1);
		do {

		} while (std::ranges::next_permutation(p).found);
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
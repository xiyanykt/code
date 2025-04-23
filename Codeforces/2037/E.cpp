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

	// answer("IMPOSSIBLE");

	auto solve = [&]() {
		int n;
		std::cin >> n;

		auto query = [&](int l, int r) {
			assert(l < r);
			std::cout << std::format("? {} {}", l, r) << std::endl;
			int t;
			std::cin >> t;
			return t;
		};

		auto answer = [&](const std::string & s) {
			std::cout << std::format("! {}", s) << std::endl;
		};

		std::string s = "";
		std::vector<int>f(n + 1);
		for (int r = 2; r <= n; r += 1) {
			f[r] = query(1, r);
		}

		int j = 0;
		for (int r = 2; r <= n; r += 1) {
			if (f[r - 1] == 0 and f[r] != 0) {
				j = r;
				break;
			}
		}
		if (not j) {
			answer("IMPOSSIBLE");
			return ;
		}
		s = std::string(n, '0');
		s[j - 1] = '1';
		for (int t = 0; t < j - f[j] - 1; t += 1) {
			s[t] = '1';
		}
		for (int i = j + 1; i <= n; i += 1) {
			if (f[i] > f[i - 1]) {
				s[i - 1] = '1';
			}
		}
		answer(s);
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
// 01001
// 3
// 101
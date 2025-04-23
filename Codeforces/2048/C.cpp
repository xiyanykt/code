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
		std::string s;
		std::cin >> s;

		int n = s.length();
		s = ' ' + s;

		auto answer = [&](int l1, int r1, int l2, int r2) {
			std::cout << std::format("{} {} {} {}\n", l1, r1, l2, r2);
		};

		if (std::ranges::count(s, '1') == 1) {
			if (n == 1) {
				answer(1, 1, 1, 1);
			} else if (n == 2) {
				answer(1, 1, 1, 2);
			} else {
				answer(1, n - 1, 1, n);
			}
			return ;
		}

		if (std::ranges::count(s, '1') == n) {
			answer(1, n, 1, 1);
			return ;
		}

		int f = 0;
		int j = n - s.find('0') + 1;
		std::vector<int>cur {};
		for (int i = 1; i + j - 1 <= n; i += 1) {
			auto t = std::string() + " " + s.substr(i, j);
			std::vector<int>rec {};
			for (int a = j, b = n, p = 0; a >= 1; a -= 1, b -= 1, p += 1) {
				if (t[a] != s[b]) {
					rec.push_back(p);
				}
			}
			std::ranges::reverse(rec);
			if (chmax(cur, rec)) {
				f = i;
			}
		}
		answer(1, n, f, f + j - 1);
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
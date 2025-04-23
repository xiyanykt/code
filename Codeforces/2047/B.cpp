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

		std::string s;
		std::cin >> s;

		if (s == std::string(n, s[0])) {
			std::cout << s << '\n';
			return ;
		}

		int cnt = 1E9;
		std::array<int, 26> rec {};
		for (const auto & c : s) {
			rec[c - 'a'] += 1;
		}

		int a = 0, b = 0, c = n, d = 0;
		for (int x = 0; x < 26; x += 1) {
			if (rec[x]) {
				if (a < rec[x]) {
					a = rec[x];
					b = x;
				}
				if (c >= rec[x]) {
					c = rec[x];
					d = x;
				}
			}
		}

		for (int i = 0; i < n; i += 1) {
			if ((s[i] - 'a') == d) {
				s[i] = 'a' + b;
				break;
			}
		}
		std::cout << s << '\n';
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
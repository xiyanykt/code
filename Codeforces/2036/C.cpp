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
constexpr void chmax(T& x, T y) {
	if (y > x) {
		x = y;
	}
}

template<class T>
constexpr void chmin(T& x, T y) {
	if (y < x) {
		x = y;
	}
}

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout << std::fixed << std::setprecision(13);

	auto solve = [&]() {
		std::string s;
		std::cin >> s;

		int n = s.size();
		if (n <= 3) {
			int q;
			std::cin >> q;
			while (q--) {
				int i, x;
				std::cin >> i >> x;
				std::cout << "NO\n";
			}
			return;
		}

		s = ' ' + s;
		int q;
		std::cin >> q;

		int cnt = 0;
		for (int i = 1; i + 3 <= n; i += 1) {
			if (std::string() + s[i] + s[i + 1] + s[i + 2] + s[i + 3] == "1100") {
				cnt += 1;
			}
		}

		auto ok = [&](int i) {
			return (i >= 1 and i + 3 <= n and std::string() + s[i] + s[i + 1] + s[i + 2] + s[i + 3] == "1100");
		};

		while (q--) {
			int i, x;
			std::cin >> i >> x;

			for (const auto & c : {i - 3, i - 2, i - 1, i, i + 1, i + 2, i + 3}) {
				cnt -= ok(c);
			}
			s[i] = '0' + x;
			for (const auto & c : {i - 3, i - 2, i - 1, i, i + 1, i + 2, i + 3}) {
				cnt += ok(c);
			}
			std::cout << (cnt >= 1 ? "YES\n" : "NO\n");
		}
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
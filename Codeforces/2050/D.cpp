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
		for (int i = 0; i < n; i += 1) {
			int x = -1;
			char t = s[i];
			for (int j = i + 1; j < std::min(n, i + 10); j += 1) {
				int l = j - i;
				if (t < char(s[j] - l)) {
					x = l;
					t = char(s[j] - l);
				}
			}
			if (x == -1) {
				std::cout << s[i];
			} else {
				std::cout << t;
				for (int j = i + x - 1; j >= i; j -= 1) {
					std::swap(s[j], s[j + 1]);
				}
				s[i] = t;
			}
		}
		std::cout << '\n';
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
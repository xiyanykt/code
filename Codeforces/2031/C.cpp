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

constexpr int Kn = 1E6;

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout << std::fixed << std::setprecision(13);

	auto solve = [&]() {
		int n;
		std::cin >> n;

		if (n % 2 == 0) {
			for (int i = 1, x = 1; i <= n; i += 2, x += 1) {
				std::cout << x << ' ' << x << ' ';
			}
			std::cout << '\n';
		} else if (n <= 25) {
			std::cout << -1 << '\n';
		} else {
			// a^2 + b^2 = c^2 \to 9 + 16 = 25
			std::vector<int>p(n + 1);
			p[1] = p[1 + 9] = p[1 + 9 + 16] = 1;
			p[1 + 9 + 16 + 1] = p[1 + 9 + 16 - 3] = 2;
			p[1 + 9 + 16 - 1] = p[1 + 9 + 16 - 2] = 3;
			std::set<int>s;
			for (int i = 1, x = 4; i <= n; i += 1) {
				if (p[i]) {
					continue;
				} else {
					if (s.contains(x)) {
						p[i] = x++;
					} else {
						p[i] = x;
						s.insert(x);
					}
				}
			}
			for (int i = 1; i <= n; i += 1) {
				std::cout << p[i] << " \n"[i == n];
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

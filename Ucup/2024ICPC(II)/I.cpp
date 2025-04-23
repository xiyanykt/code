#include<bits/stdc++.h>

using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128_t;
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
		int x;
		std::cin >> x;

		std::array<int, 32>f {};
		for (int i = 0; i <= 31; i += 1) {
			f[i] = (x >> i & 1);
		}

		for (int i = 0; i <= 31; i += 1) {
			if (f[i] == 1) {
				int j = i + 1;
				while (j <= 31 and f[j] == 0) {
					j += 1;
				}
				j -= 1;
				for (int k = i; k <= j; k += 1) {
					f[k] = -1;
				}
				f[j] = 1;
				i = j;
			}
		}

		for (int i = 0; i <= 30; i += 1) {
			if (f[i] == 0 and f[i + 1] == 0) {
				std::cout << "NO\n";
				return ;
			}
		}

		std::cout << "YES\n";
		for (int i = 0; i < 4; i += 1) {
			for (int j = 0; j < 8; j += 1) {
				std::cout << f[i * 8 + j] << " \n"[j == 7];
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
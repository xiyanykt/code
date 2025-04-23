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

constexpr int Mod = 998244353;

constexpr int mul(int a, int b) {
	return (i64(a) * b) % Mod;
}

constexpr int add(int a, int b) {
	return (i64(a) + b) % Mod;
}

constexpr int power(int a, int b) {
	int res = 1;
	for (; b != 0; b >>= 1, a = mul(a, a)) {
		if (b & 1) {
			res = mul(res, a);
		}
	}
	return res;
}

constexpr int inv(int x) {
	return power(x, Mod - 2);
}

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout << std::fixed << std::setprecision(13);

	auto solve = [&]() {
		int x, y;
		std::cin >> x >> y;

		int a0, a1, b;
		std::cin >> a0 >> a1 >> b;

		int p0 = mul(a0 , inv(add(a0, a1)));
		int p1 = mul(a1, inv(add(a0, a1)));
		int ans = 0, pp = 1;

		while (x > 0 and y > 0) {
			if (x > y) {
				int div = x / y, mod = x % y;
				ans = add(ans, mul(pp, add(1, Mod - power(p1, div))));
				pp = mul(pp, power(p1, div));
				x = mod;
			} else {
				int div = y / x, mod = y % x;
				if (mod == 0) {
					ans = add(ans, mul(pp, power(p0, div)));
				}
				pp = mul(pp, power(p0, div));
				y = mod;
			}
		}

		std::cout << ans << '\n';
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
#include<bits/stdc++.h>

using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128;
using f128 = __float128;

#ifndef ONLINE_JUDGE
#include "algo\debug.hpp"
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

constexpr int N = 5E3;
int c[N + 1][N + 1];

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout << std::fixed << std::setprecision(13);

	int n, m, q;
	std::cin >> n >> m >> q;

	auto add = [&](int x, int y) {
		return (i64(x) + y) % q;
	};
	auto mul = [&](int x, int y) {
		return (1LL * x * y % q);
	};

	c[1][0] = c[1][1] = 1;
	for (int i = 2; i <= N; i += 1) {
		c[i][0] = c[i][i] = 1;
		for (int j = 1; j <= i - 1; j += 1) {
			c[i][j] = add(c[i - 1][j], c[i - 1][j - 1]);
		}
	}

	auto power = [&](int a, i64 b) {
		int res = 1;
		for (; b > 0; a = mul(a, a), b >>= 1) {
			if (b & 1) {
				res = mul(res, a);
			}
		}
		return res;
	};

	int ans = 0;
	for (int k = 1; k <= n; k += 1) {
		int res = c[n][k];
		int x = power(2, mul(m - 1, n - k));
		int y = power(power(2, k) - 1, m - 1);
		ans = add(ans, mul(mul(res, x), y));
	}

	std::cout << ans << '\n';
	return 0;
}
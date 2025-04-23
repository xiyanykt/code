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

	int n;
	std::cin >> n;

	std::vector<i64>w(n + 1), v(n + 1), c(n + 1);
	for (int i = 1; i <= n; i += 1) {
		std::cin >> w[i] >> v[i] >> c[i];
	}

	std::vector<int>par(n + 1);
	std::ranges::iota(par, 0);
	std::sort(par.begin() + 1, par.end(), [&](const auto & i, const auto & j) {
		return c[i] * w[j] < c[j] * w[i];
	});

	i64 W = 0;
	i64 ans = 0;
	for (int i = 1; i <= n; i += 1) {
		ans += v[par[i]] - c[par[i]] * W;
		W += w[par[i]];
	}

	std::cout << ans << '\n';

	return 0;
}
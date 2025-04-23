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

	auto solve = [&]() {
		int n;
		std::cin >> n;

		std::vector<i64>a(n + 1), b(n + 1);
		for (int i = 1; i <= n; i += 1) {
			std::cin >> a[i];
		}

		for (int i = 1; i <= n; i += 1) {
			std::cin >> b[i];
		}

		int top = 0;
		std::vector<int>lsh(n + 1), rsh(n + 1), stk(n + 1);
		for (int i = 1; i <= n; i += 1) {
			int k = top;
			while (k > 0 && b[i] < b[stk[k]]) {
				k -= 1;
			}
			if (k > 0) {
				rsh[stk[k]] = i;
			}
			if (k < top) {
				lsh[i] = stk[k + 1];
			}
			stk[top = (k += 1)] = i;
		}

		constexpr i64 inf = 2E18;
		constexpr int Kn = 61;
		std::array<i64, Kn>t {};
		std::vector<std::array<i64, Kn>>dp(n + 1);
		auto dfs = [&](this auto && dfs, int p, int l, int r) {
			if (p == 0) {
				return ;
			}
			if (l == r) {
				dp[p][0] = a[l];
				for (int k = 1; k < Kn; k += 1) {
					dp[p][k] = (dp[p][k - 1] + b[l] - 1) / b[l];
				}
				return ;
			}
			dfs(lsh[p], l, p - 1);
			dfs(rsh[p], p + 1, r);
			dp[p].fill(inf);
			for (int x = 0; x < Kn; x += 1) {
				for (int y = 0; x + y < Kn; y += 1) {
					chmin(dp[p][x + y], std::max({dp[lsh[p]][x], dp[rsh[p]][y], a[p]}));
				}
			}
			for (int k = 1; k < Kn; k += 1) {
				chmin(dp[p][k], (dp[p][k - 1] + b[p] - 1) / b[p]);
			}
		};
		dfs(stk[1], 1, n);

		for (int k = 0; k < Kn; k += 1) {
			if (dp[stk[1]][k] <= 1) {
				std::cout << k << '\n';
				return ;
			}
		}
		assert(false);
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
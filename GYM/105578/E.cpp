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

	int t;
	std::cin >> t;
	std::array<int, 4> h {};
	std::cin >> h[0] >> h[1] >> h[2] >> h[3];

	constexpr int Kn = 16;
	constexpr int inf = 1E9;
	std::vector dp(Kn, std::vector<int>(1 << Kn, inf));
	dp[0][0] = 0;
	for (int a = 0; a < 1 << Kn; a += 1) {
		for (int b = 0; b < Kn; b += 1) {
			for (int i = 0; i < 4; i += 1) {
				int u = b ^ 1 << i;
				int v = a | 1 << u;
				chmin(dp[u][v], dp[b][a] + h[0]);
			}
			for (int i = 0; i < 3; i += 2) {
				int u = b ^ 3 << i;
				int v = a | 1 << u;
				chmin(dp[u][v], dp[b][a] + h[1]);
			}
			for (int i = 0; i < 2; i += 1) {
				int u = b ^ 5 << i;
				int v = a | 1 << u;
				chmin(dp[u][v], dp[b][a] + h[2]);
			}
			int u = b ^ 15;
			int v = a | 1 << u;
			chmin(dp[u][v], dp[b][a] + h[3]);
		}
	}

	std::vector<int>f(1 << Kn, inf);
	for (int s = (1 << Kn) - 1; s >= 1; s -= 1) {
		for (int i = 0; i < Kn; i += 1) {
			chmin(f[s], dp[i][s]);
		}
		for (int i = 0; i < Kn; i += 1) {
			if (s >> i & 1) {
				chmin(f[s ^ 1 << i], f[s]);
			}
		}
	}

	auto solve = [&]() {
		int m;
		std::cin >> m;

		int s = 0;
		for (int i = 0; i < m; i += 1) {
			int t = 0;
			for (int j = 0; j < 4; j += 1) {
				char c;
				std::cin >> c;
				if (c == '1') {
					t |= 1 << j;
				}
			}
			s |= 1 << (15 ^ t);
		}
		std::cout << f[s] << '\n';
	};

	while (t--) {
		solve();
	}
	return 0;
}
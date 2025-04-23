#include<bits/stdc++.h>

using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;

#ifndef ONLINE_JUDGE
#include "algo\debug.hpp"
#else
#define debug(...) (void)42
#endif

constexpr i64 inf = 1E17;

template<class Tp>
void chmax(Tp& x, Tp y) {
	x = std::max(x, y);
}
template<class Tp>
void chmin(Tp& x, Tp y) {
	x = std::min(x, y);
}

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cout << std::fixed << std::setprecision(13);

	auto solve = [&]() {
		int n, m;
		std::cin >> n >> m;

		std::vector a(n + 1, std::vector<i64>(m + 1));
		for (int i = 1; i <= n; i += 1) {
			for (int j = 1; j <= m; j += 1) {
				std::cin >> a[i][j];
			}
		}

		std::vector dp(n + 2, std::vector<i64>(m + 1, -inf));
		std::fill(dp[1].begin(), dp[1].end(), 0);
		
		std::vector<i64>pref(m + 2), surf(m + 2);
		for (int i = 1; i <= n; i += 1) {
			pref.assign(m + 2, 0);
			surf.assign(m + 2, 0);
			for (int j = 1; j <= m; j += 1) {
				pref[j] = std::max(pref[j - 1] + a[i][j], a[i][j]);
			}
			for (int j = m; j >= 1; j -= 1) {
				surf[j] = std::max(surf[j + 1] + a[i][j], a[i][j]);
			}

			i64 p = -inf, s = -inf;
			for (int j = 1; j <= m; j += 1) {
				p = std::max(p + a[i][j], pref[j] + dp[i][j]);
				chmax(dp[i + 1][j], p + surf[j] - a[i][j]);
			}
			for (int j = m; j >= 1; j -= 1) {
				s = std::max(s + a[i][j], surf[j] + dp[i][j]);
				chmax(dp[i + 1][j], s + pref[j] - a[i][j]);
			}
		}

		i64 ans = *std::max_element(dp[n + 1].begin() + 1, dp[n + 1].end());
		std::cout << ans << "\n";
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
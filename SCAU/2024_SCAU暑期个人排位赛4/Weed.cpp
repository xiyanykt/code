#include<bits/stdc++.h>

using i64 = int64_t;

#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) (void)42
#endif

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, k;
	std::cin >> n >> k;

	std::vector<int>a(n + 1);
	for (int i = 1; i <= n; i += 1) {
		std::cin >> a[i];
	}

	std::ranges::sort(a);

	constexpr int inf = 1E8;

	std::vector dp(n + 1, std::vector<int>(33, inf));
	dp[0][0] = 0;
	for (int i = 1; i <= n; i += 1) {
		dp[i][0] = i;
		int p = std::ranges::upper_bound(a, a[i] / 2) - a.begin() - 1;
		for (int j = 1; j <= 31; j += 1) {
			dp[i][j] = std::min(dp[i - 1][j] + 1, dp[p][j - 1]);
		}
	}

	for (int j = 0; j <= 31; j += 1) {
		if (dp[n][j] <= k) {
			// std::cout << std::format("{} {}\n", j, dp[n][j]);
			std::cout << j << " " << dp[n][j] << "\n";
			return 0;
		}
	}

	return 0;
}
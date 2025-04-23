#include<bits/stdc++.h>

using i64 = int64_t;

#define int i64

#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) (void)42
#endif

signed main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

#define int i64

	auto solve = [&]() {
		int n;
		std::cin >> n;

		std::vector<int>a(n + 1);
		for (int i = 1; i <= n; i += 1) {
			std::cin >> a[i];
		}

		std::sort(a.begin() + 1, a.end());

		a.erase(std::unique(a.begin() + 1, a.end()), a.end());

		int g = 0;
		n = a.size() - 1;
		for (int i = 2; i <= n; i += 1) {
			g = std::gcd(g, a[i] - a[i - 1]);
		}

		std::cout << g << "\n";
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}

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

	using f64 = long double;

	std::cout << std::fixed << std::setprecision(9);

	auto solve = [&]() {
		int n;
		std::cin >> n;

		std::vector<f64>a(n + 1);
		for (int i = 1; i <= n; i += 1) {
			std::cin >> a[i];
		}

		i64 ans = 0;
		
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
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

	auto solve = [&]() {
		int n;
		std::cin >> n;

		std::vector<int>a(n + 1), b(n + 1);
		for (int i = 1; i <= n; i += 1) {
			std::cin >> a[i];
		}
		for (int i = 1; i <= n; i += 1) {
			std::cin >> b[i];
		}

		int ans = 0, clz = 0;
		for (int i = 1; i <= n; i += 1) {
			if (a[i] == b[i]) {
				clz += 1;
			}
			if (a[i] > b[i]) {
				ans += 1;
			}
		}

		clz += 1;

		std::cout << (ans + clz / 2) << "\n";
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
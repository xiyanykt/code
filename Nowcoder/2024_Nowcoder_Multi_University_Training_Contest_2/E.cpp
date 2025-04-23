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
		i64 x;
		std::cin >> x;

		if (x == 1) {
			std::cout << "-1\n";
			return;
		}

		if (x & 1) {
			std::cout << (x - 1) << "\n";
		} else {
			if (__builtin_popcountll(x) == 1) {
				std::cout << -1 << "\n";
			} else {
				std::cout << (x - (x & -x)) << "\n";
			}
		}
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
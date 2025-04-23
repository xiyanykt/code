#include<bits/stdc++.h>

using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;

#ifndef ONLINE_JUDGE
#include "algo\debug.hpp"
#else
#define debug(...) (void)42
#endif

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cout << std::fixed << std::setprecision(13);

	auto solve = [&]() {
		i64 l, x, y;
		std::cin >> l >> x >> y;

		if (l * l >= x * x + y * y) {
			std::cout << "Yes\n";
			std::cout << 0 << "\n";
			return;
		}
		if (l * l >= (x - l) * (x - l) + y * y) {
			std::cout << "Yes\n";
			std::cout << l << "\n";
			return;
		}
		std::cout << "No\n";
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
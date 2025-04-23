#include<bits/stdc++.h>

using i64 = int64_t;
using f64 = long double;

#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) (void)42
#endif

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cout << std::fixed << std::setprecision(13);

	auto solve = [&]() {
		int x, y, a, b;
		std::cin >> x >> y >> a >> b;

		x *= -1;

		f64 res = std::sqrt(1.l * (x - a) * (x - a) + 1.l * (y - b) * (y - b));

		x *= -1;
		y *= -1;

		f64 ans = std::sqrt(1.l * (x - a) * (x - a) + 1.l * (y - b) * (y - b));

		std::cout << std::min(ans, res) << std::endl;
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}

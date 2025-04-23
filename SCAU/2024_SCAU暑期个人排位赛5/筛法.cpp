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

	// const int T = 100;

	// for (int t = 1; t <= T; t += 1) {
	// 	i64 ans = 0;
	// 	for (int i = 1; i <= t; i += 1) {
	// 		for (int j = 1; j <= t; j += 1) {
	// 			ans += (std::gcd(i, j) == 1 ? t / (std::max(i, j)) : 0);
	// 		}
	// 	}
	// 	std::cout << ans << "\n";
	// }

	i64 n;
	std::cin >> n;

	std::cout << n * n << "\n";

	return 0;
}
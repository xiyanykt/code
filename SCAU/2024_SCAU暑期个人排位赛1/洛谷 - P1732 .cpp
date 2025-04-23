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

		std::set<int>S;

		i64 ans = 0;
		for (int i = 1; i <= n; i += 1) {
			int x;
			std::cin >> x;
			if (i == 1) {
				ans += x;
				S.insert(x);
				continue;
			}
			int res = std::numeric_limits<int>::max();
			auto y = S.lower_bound(x);
			if (y != S.end()) {
				res = std::min(res, (*y) - x);
			}
			if (y != S.begin()) {
				res = std::min(res, x - (*(std::prev(y))));
			}
			S.insert(x);
			ans += res;
		}
		std::cout << ans << "\n";
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
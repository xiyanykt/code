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
		int n, m, a, b;
		std::cin >> n >> m >> a >> b;

		i64 v = 1LL * n * m;

		auto NO = [&]() {
			std::cout << "No\n";
		};
		auto YES = [&]() {
			std::cout << "Yes\n";
		};

		if (v % 2 != 0) {
			NO();
			return;
		}

		if (v == 2) {
			YES();
			return;
		}

		if (n == 1 or m == 1) {
			a ? YES() : NO();
			return;
		}

		b ? YES() : NO();

	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
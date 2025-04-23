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

		std::string s;
		std::cin >> s;

		if (n < 11) {
			std::cout << "NO\n";
		} else if (n == 11) {
			std::cout << (s[0] == '8' ? "YES\n" : "NO\n");
		} else {
			int j = n + 1;
			for (int i = 1; i <= n; i += 1) {
				if (s[i - 1] == '8') {
					j = i;
					break;
				}
			}
			std::cout << (n - (j - 1) >= 11 ? "YES\n" : "NO\n");
		}
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
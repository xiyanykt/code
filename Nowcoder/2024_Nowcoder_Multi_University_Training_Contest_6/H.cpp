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
		std::string s;
		std::cin >> s;

		int n = s.size();
		s = " " + s;

		std::vector<int>cnt3(n + 1);
		for (int i = 1; i <= n; i += 1) {
			cnt3[i] += cnt3[i - 1] + (s[i] == '3');
		}

		if (n >= 10) {
			for (int i = 10; i <= n; i += 1) {
				if (cnt3[i] - cnt3[i - 10] == 10) {
					std::cout << "invalid\n";
					return;
				}
			}
		}

		std::vector<int>cnt5(n + 1);
		for (int i = 1; i <= n; i += 1) {
			cnt5[i] += cnt5[i - 1] + (s[i] == '5' or s[i] == 'U');
		}

		if (n >= 90) {
			for (int i = 90; i <= n; i += 1) {
				if (cnt5[i] - cnt5[i - 90] == 0) {
					std::cout << "invalid\n";
					return;
				}
			}
		}

		std::vector<int>v;
		for (int i = 1; i <= n; i += 1) {
			if (s[i] == '5' or s[i] == 'U') {
				v.push_back(i);
			}
		}

		for (int i = 1; i < v.size(); i += 1) {
			if (s[v[i]] == s[v[i - 1]] and s[v[i]] == '5') {
				std::cout << "invalid\n";
				return;
			}
		}

		std::cout << "valid\n";
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}

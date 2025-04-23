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

	int n;
	std::cin >> n;

	std::string s;
	std::cin >> s;
	s = " " + s;

	std::vector<int>dis(n + 1);
	for (int i = 1; i <= n; i += 1) {
		std::cin >> dis[i];
	}

	std::vector<int>st(n + 1);

	int j = 1;
	while (j >= 1 and j <= n) {
		if (st[j]) {
			std::cout << "INFINITE\n";
			std::exit(0);
		}
		st[j] += 1;
		j += dis[j] * (s[j] == '>' ? 1 : -1);
	}
	std::cout << "FINITE\n";
	return 0;
}
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

	std::string g[3];
	std::cin >> g[1] >> g[2];
	g[1] = " " + g[1];
	g[2] = " " + g[2];

	int ans = 0;
	std::vector<int>f(3, -2 * n);
	for (int i = 1; i <= n; i += 1) {
		std::vector<int>p(3, -2 * n);
		if (g[1][i] == 'R' and g[2][i] == 'R') {
			p[1] = std::max({2, f[1] + 1, f[2] + 2});
			p[2] = std::max({2, f[2] + 1, f[1] + 2});
		} else if (g[1][i] == 'R') {
			p[1] = std::max(1, f[1] + 1);
		} else if (g[2][i] == 'R') {
			p[2] = std::max(1, f[2] + 1);
		}
		ans = std::max({ans, p[1], p[2]});
		f.swap(p);
	}

	std::cout << std::max(ans - 1, 0) << "\n";
	return 0;
}
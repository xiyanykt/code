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

	int n, x, y;
	std::cin >> n >> x >> y;

	std::vector<int>a(n + 1), b(n + 1);
	for (int i = 1; i <= n; i += 1) {
		std::cin >> a[i] >> b[i];
	}

	std::sort(a.begin() + 1, a.end());
	std::sort(b.begin() + 1, b.end());

	i64 ans = 0;
	for (int i = 1; i <= n; i += 1) {
		ans += std::max({(a[i] - b[i])*y, (b[i] - a[i])*x});
	}

	std::cout << ans << "\n";

	return 0;
}
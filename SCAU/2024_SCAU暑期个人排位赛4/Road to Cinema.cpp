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

#define int long long

	int n, k, s, t;
	std::cin >> n >> k >> s >> t;

	std::vector<int>c(n + 1), v(n + 1), g(k + 2);
	for (int i = 1; i <= n; i += 1) {
		std::cin >> c[i] >> v[i];
	}

	for (int i = 1; i <= k; i += 1) {
		std::cin >> g[i];
	}
	g[k + 1] = s;

	std::ranges::sort(g);

	auto work = [&](int x) {
		int res = 0;
		for (int i = 1; i <= k + 1; i += 1) {
			int len = g[i] - g[i - 1];
			if (len > x) {
				return true;
			}
			if (2 * len <= x) {
				res += len;
			} else {
				int acl = x - len;
				int nor = len - acl;
				res += nor * 2 + acl;
			}
		}
		return res > t;
	};

	int o = *std::ranges::partition_point(std::ranges::iota_view(1LL, (i64)2E9 + 1), work);

	// std::cerr << o << "\n";

	int ans = std::numeric_limits<i64>::max();

	for (int i = 1; i <= n; i += 1) {
		if (v[i] >= o) {
			ans = std::min(ans, c[i]);
		}
	}
	if (ans == std::numeric_limits<i64>::max()) {
		ans = -1;
	}
	std::cout << ans << "\n";
	return 0;
}
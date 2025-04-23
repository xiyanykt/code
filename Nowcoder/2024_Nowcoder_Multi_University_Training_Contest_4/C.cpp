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

		std::vector<int>a(n + 1);
		for (int i = 1; i <= n; i += 1) {
			std::cin >> a[i];
		}

		int ans = 0;
		int clz = 0;
		std::vector<int>vis(n + 1);
		for (int i = 1; i <= n; i += 1) {
			if (vis[i]) {
				continue;
			}
			auto dfs = [&](auto && self, int u, int d) {
				if (vis[u]) {
					return d;
				} else {
					vis[u] = 1;
					return self(self, a[u], d + 1);
				}
				return -1;
			};
			int gao = dfs(dfs, i, 0);
			ans += gao / 3;
			if (gao % 3 == 2) {
				clz += 1;
			}
		}

		std::cout << ans + (clz + 1) / 2 << std::endl;
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
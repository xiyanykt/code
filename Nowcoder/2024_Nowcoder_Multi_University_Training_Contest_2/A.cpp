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
		int n, m, k;
		std::cin >> n >> m >> k;

		if (k < n + m) {
			std::cout << "No\n";
			return;
		}

		int x, y;
		char t;
		std::cin >> x >> y >> t;

		std::vector g(n + 1, std::vector<char>(m + 1));
		if (t == 'A') {
			for (int i = 1; i <= n; i += 1) {
				for (int j = 1; j <= m; j += 1) {
					g[i][j] = 'A';
				}
			}
			for (int i = 1; i <= n; i += 1) {
				for (int j = 1; j <= m; j += 1) {

				}
			}
		} else {
			for (int i = 1; i <= n; i += 1) {
				for (int j = 1; j <= m; j += 1) {
					g[i][j] = 'B';
				}
			}

		}
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
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

		std::vector<int>par(n + 1);
		std::iota(par.begin() + 1, par.end(), 1);
		std::vector<int>w(n + 1);

		auto find = [&](auto && self, int x)->int {
			if (par[x] != x) {
				int u = self(self, par[x]);
				w[x] += w[par[x]];
				par[x] = u;
			}
			return par[x];
		};

		std::vector<int>clz(n + 1);
		for (int i = 1; i <= n - 1; i += 1) {
			int a, b, c;
			std::cin >> a >> b >> c;
			int x = find(find, a), y = find(find, b);
			par[y] = x;
			w[y] = w[a] + 1;
			clz[x] = std::max((int)clz[x], (int)clz[y] + w[y]);
			std::cout << clz[find(find, c)] << " ";
		}
		std::cout << "\n";
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
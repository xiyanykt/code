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

	int n, m;
	std::cin >> n >> m;

	std::map<int, std::vector<std::pair<int, int>>>rec;
	for (int i = 1; i <= n; i += 1) {
		for (int j = 1; j <= m; j += 1) {
			int c;
			std::cin >> c;
			rec[c].emplace_back(i, j);
		}
	}

	i64 ans = 0;
	for (const auto & [x, v] : rec) {
		std::vector<int>l, r;
		for (const auto & [a, b] : v) {
			l.push_back(a);
			r.push_back(b);
		}
		std::ranges::sort(l);
		std::ranges::sort(r);
		i64 preL = 0, preQ = 0;
		for (int j = 0; j < l.size(); j += 1) {
			ans += 1LL * j * l[j] - preL;
			ans += 1LL * j * r[j] - preQ;
			preL += l[j];
			preQ += r[j];
		}
	}

	std::cout << ans << "\n";

	return 0;
}
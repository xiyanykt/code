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

	// std::map<int, std::vector<int>>vec;

	std::vector vec(m + 1, std::vector<int>());

	for (int i = 1; i <= n; i += 1) {
		int p, c;
		std::cin >> p >> c;
		vec[p].emplace_back(c);
	}

	for (int j = 1; j <= m; j += 1) {
		std::ranges::sort(vec[j]);
	}

	i64 ans = std::numeric_limits<i64>::max();
	for (int i = std::max(1, (int)vec[1].size()); i <= n; i += 1) {
		i64 res = 0;
		int ned = i - vec[1].size();
		std::vector<int>remain;
		for (int j = 2; j <= m; j += 1) {
			int o = (vec[j].size() < i ? 0 : vec[j].size() - i + 1);
			for (int k = 0; k < o; k += 1) {
				ned -= 1;
				res += vec[j][k];
			}
			for (int k = o; k < vec[j].size(); k += 1) {
				remain.push_back(vec[j][k]);
			}
		}
		std::ranges::sort(remain, std::greater());
		while (ned > 0) {
			ned -= 1;
			res += remain.back();
			remain.pop_back();
		}
		ans = std::min(ans, res);
	}
	std::cout << ans << "\n";
	return 0;
}
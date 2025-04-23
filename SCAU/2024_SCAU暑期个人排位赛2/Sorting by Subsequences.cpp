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

	std::vector<int>a(n + 1);
	for (int i = 1; i <= n; i += 1) {
		std::cin >> a[i];
	}

	std::vector<int>p(n + 1);
	std::iota(p.begin() + 1, p.end(), 1);
	std::sort(p.begin() + 1, p.end(), [&](const auto & i, const auto & j) {
		return a[i] < a[j];
	});

	std::vector<std::vector<int>>ans;
	std::vector<int>vis(n + 1);

	for (int i = 1; i <= n; i += 1) {
		if (vis[i]) {
			continue;
		}
		int x = i;
		std::vector<int>path;
		while (not vis[x]) {
			vis[x] += 1;
			path.push_back(x);
			x = p[x];
		}
		ans.push_back(path);
	}

	std::cout << ans.size() << "\n";
	for (const auto & v : ans) {
		std::cout << v.size() << " ";
		for (const auto & c : v) {
			std::cout << c << " \n"[c == v.back()];
		}
	}

	return 0;
}
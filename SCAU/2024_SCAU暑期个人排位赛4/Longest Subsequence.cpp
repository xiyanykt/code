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

	std::vector<int>a(n + 1);

	const int N = 1E6;

	std::vector<int>cnt(N + 1);

	for (int i = 1; i <= n; i += 1) {
		int x;
		std::cin >> x;
		a[i] = x;
		if (x <= m) {
			cnt[x] += 1;
		}
	}

	for (int i = m; i >= 1; i -= 1) {
		for (int j = 2 * i; j <= m; j += i) {
			cnt[j] += cnt[i];
		}
	}

	int ans = 1;
	for (int i = 1; i <= m; i += 1) {
		if (cnt[ans] < cnt[i]) {
			ans = i;
		}
	}

	std::cout << std::format("{} {}\n", ans, cnt[ans]);

	for (int i = 1; i <= n; i += 1) {
		if (ans % a[i] == 0) {
			std::cout << i << " ";
		}
	}

	return 0;
}
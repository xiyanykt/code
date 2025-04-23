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

	constexpr int inf = 1E9;

	int n, q;
	std::cin >> n >> q;

	constexpr int N = 50;

	std::vector<int>pos(N + 1, inf);
	for (int i = 1; i <= n; i += 1) {
		int c;
		std::cin >> c;
		pos[c] = std::min(pos[c], i);
	}

	while (q--) {
		int c;
		std::cin >> c;
		int j = pos[c];
		std::cout << j << " ";
		pos[c] = 1;
		for (int i = 1; i <= N; i += 1) {
			if (pos[i] == inf or i == c) {
				continue;
			}
			if (pos[i] < j) {
				pos[i] += 1;
			}
		}
	}

	return 0;
}
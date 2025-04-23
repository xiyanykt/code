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

	int N;
	std::cin >> N;

	std::map<int, std::vector<int>>rec;
	std::vector<int>clz(N + 1);
	std::vector<int>gao(N + 1), zhi(N + 1);

	for (int i = 1; i <= N; i += 1) {
		int t, x;
		std::cin >> t >> x;
		if (t == 1) {
			rec[x].push_back(i);
			gao[i] = 1;
		} else {
			if (not rec.contains(x)) {
				std::cout << "-1\n";
				return 0;
			}
			zhi[i] = 1;
			clz[rec[x].back()] = 1;
			rec[x].pop_back();
			if (rec[x].empty()) {
				rec.erase(x);
			}
		}
	}

	int c = 0;
	int p = 0;
	for (int i = 1; i <= N; i += 1) {
		p += clz[i];
		if (zhi[i]) {
			p -= 1;
		}
		c = std::max(c, p);
	}

	std::cout << c << "\n";

	for (int i = 1; i <= N; i += 1) {
		if (not gao[i]) {
			continue;
		}
		std::cout << clz[i] << " \n"[i == N];
	}

	return 0;
}
#include<bits/stdc++.h>

using i64 = int64_t;

#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) (void)42
#endif

struct Q {
	int l, r, t, e;
};

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, m;
	std::cin >> n >> m;

	const int B = std::pow(n, 2.0 / 3.0);
	std::vector<int>a(n + 1);
	for (int i = 1; i <= n; i += 1) {
		std::cin >> a[i];
	}

	std::vector<int>bel(n + 1);
	for (int i = 1; i <= n; i += 1) {
		bel[i] = (i - 1) / B + 1;
	}

	std::vector<Q>qry(m + 1);
	for (int i = 1; i <= m; i += 1) {
		char o;
		std::cin >> o;
		
	}

	return 0;
}
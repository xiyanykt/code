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

	for (int i = 1; i <= n; i += 1) {
		int x;
		std::cin >> x;

		std::cout << (std::__lg(x)) << "\n";

	}

	return 0;
}
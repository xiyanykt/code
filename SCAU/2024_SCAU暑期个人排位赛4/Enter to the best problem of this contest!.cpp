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

	auto ask = [&](int x) {
		std::cout << x << std::endl;
		int y;
		std::cin >> y;
		return y;
	};
	auto ans = [&](int x) {
		std::cout << "! " << x << std::endl;
	};

	int dep = ask(1);
	if (dep == 0) {
		ans(1);
		return 0;
	}

	int j = 1 << dep;
	while (true) {
		int y = ask(j);
		if (y == 0) {
			ans(j);
			return 0;
		} else if (y == 2) {
			ans(j + 1);
			return 0;
		}
		y /= 2;
		y -= 1;
		j += 1 << y;
	}

	return 0;
}
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

	int a, b, r;
	std::cin >> a >> b >> r;

	r *= 2;

	int x = a / r;
	int y = b / r;

	std::cout << (x == 0 or y == 0 ? "Second\n" : "First\n");

	return 0;
}
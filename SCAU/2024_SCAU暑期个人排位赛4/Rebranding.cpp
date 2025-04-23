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

	int n, q;
	std::cin >> n >> q;

	std::string s;
	std::cin >> s;

	std::map<char, char>rec;
	for (char x = 'a'; x <= 'z'; x += 1) {
		rec[x] = x;
	}

	while (q--) {
		char x, y;
		std::cin >> x >> y;
		char u, v;
		for (char z = 'a'; z <= 'z'; z += 1) {
			if (rec[z] == x) {
				u = z;
			}
			if (rec[z] == y) {
				v = z;
			}
		}
		rec[u] = y, rec[v] = x;
	}

	for (const auto & c : s) {
		std::cout << rec[c];
	}

	return 0;
}
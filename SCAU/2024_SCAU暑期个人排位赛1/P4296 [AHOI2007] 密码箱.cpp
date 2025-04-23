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

	#define int long long

	i64 n;
	std::cin >> n;
	std::set<i64>S;

	for (i64 i = 1; i * i <= n; i += 1) {
		if (n % i == 0) {
			i64 y = n / i;
			for (i64 c = y; c <= n; c += y) {
				S.insert(c - 1);
				S.insert(c + 1);
			}
		}
	}

	if (S.empty()) {
		std::cout << "None\n";
	} else {
		S.insert(1);
		for (const auto & c : S) {
			if (c >= 0 and c < n and (c * c) % n == 1) {
				std::cout << c << "\n";
			}
		}
	}

	return 0;
}
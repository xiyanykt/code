#include<bits/stdc++.h>

#pragma GCC optimize("O2")
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
#pragma GCC target("sse4,popcnt,abm,mmx")

using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;

#ifndef ONLINE_JUDGE
#include "algo\debug.hpp"
#else
#define debug(...) (void)42
#endif

template<class T>
void chmax(T& x, T y) {
	x = std::max(x, y);
}

template<class T>
void chmin(T& x, T y) {
	x = std::min(x, y);
}

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::string s;
	std::cin >> s;

	int a = 0, b = 0;
	for (const auto & c : s) {
		if (c == 'Y') {
			a += 1;
		}
		if (c == '-') {
			b += 1;
		}
	}

	if (a >= 4) {
		std::cout << 1 << "\n";
	} else if (5 - a - b < 2) {
		std::cout << 0 << "\n";
	} else {
		std::cout << "-1\n";
	}
	return 0;
}

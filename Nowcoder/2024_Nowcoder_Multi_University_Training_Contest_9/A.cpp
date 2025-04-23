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

	int n, m;
	std::cin >> n >> m;

	std::vector<std::string>g(n + 1);
	for (int i = 1; i <= n; i += 1) {
		std::cin >> g[i];
		g[i] = ' ' + g[i];
	}

	int a = 1E9, b = 1E9, c = 0, d = 0;
	for (int i = 1; i <= n; i += 1) {
		for (int j = 1; j <= m; j += 1) {
			if (g[i][j] == 'x') {
				a = std::min(i, a);
				b = std::min(j, b);
				c = std::max(c, i);
				d = std::max(d, j);
			}
		}
	}

	int L = c - a + 1, H = d - b + 1;

	int y = std::gcd(L, H);

	L /= y, H /= y;

	for (int i = 0; i < L; i += 1) {
		for (int j = 0; j < H; j += 1) {
			std::cout << 'x';
		}
		std::cout << '\n';
	}
	return 0;
}

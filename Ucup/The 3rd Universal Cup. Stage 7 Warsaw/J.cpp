#include<bits/stdc++.h>

#pragma GCC optimize("O2")
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
#pragma GCC target("sse4,popcnt,abm,mmx")

using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128;
using f128 = __float128;

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

	int n = s.size();
	int ans = std::ranges::count(s, '1');

	for (int l = 0; l < n; l += 1) {
		if (s[l] == '1') {
			for (int r = l; r < n; r += 1) {
				if (s[r] == '1') {
					int cost = 0;
					for (int i = 0; i < n; i += 1) {
						if ((i >= l and i <= r) != s[i] == '1') {
							cost += 1;
						}
					}
					chmin(ans, cost);
				}
			}
		}
	}

	std::cout << ans << '\n';

	return 0;
}
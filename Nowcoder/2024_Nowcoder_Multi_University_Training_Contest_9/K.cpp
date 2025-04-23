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

#define int i64

	int n, k;
	std::cin >> n >> k;

	std::vector<int>a(n + 1);
	for (int i = 1; i <= n; i += 1) {
		std::cin >> a[i];
	}

	if (n == 1) {
		int c = 0;
		while (a[1] > 0) {
			c += 1;
			a[1] /= k;
		}
		std::cout << c << "\n";
		return 0;
	}

	std::priority_queue<int>Q;
	for (int i = 1; i <= n; i += 1) {
		Q.push(a[i]);
	}

	i64 ans = Q.top();

	if (k == 1) {
		std::cout << ans << "\n";
		return 0;
	}

	i64 res = 0;

	while (Q.top() > 0) {
		auto u = Q.top();
		Q.pop();
		res += 1;
		u /= k;
		Q.push(u);
		ans = std::min(ans, Q.top() + res);
	}

	std::cout << ans << "\n";
	return 0;
}

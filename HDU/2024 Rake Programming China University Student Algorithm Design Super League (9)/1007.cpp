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

	std::cout << std::fixed << std::setprecision(13);

	auto solve = [&]() {
		int n;
		std::cin >> n;

		std::vector<int>a(n + 1), b(n + 1);
		for (int i = 1; i <= n; i += 1) {
			std::cin >> a[i];
		}
		for (int i = 1; i <= n; i += 1) {
			std::cin >> b[i];
		}

		std::map<int, int>rec;
		for (int i = 1; i <= n; i += 1) {
			rec[a[i]] += 1;
		}

		int ans = 0;
		for (const auto & [x, v] : rec) {
			ans += v == 2;
		}
		std::cout << (ans > 0 ? "shuishui\n" : "sha7dow\n");
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
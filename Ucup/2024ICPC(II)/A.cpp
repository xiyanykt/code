#include<bits/stdc++.h>

using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128_t;
using f128 = __float128;

#ifndef ONLINE_JUDGE
#include "algo/debug.hpp"
#else
#define debug(...) (void)42
#endif

template<class T>
constexpr void chmax(T& x, T y) {
	if (y > x) {
		x = y;
	}
}

template<class T>
constexpr void chmin(T& x, T y) {
	if (y < x) {
		x = y;
	}
}

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout << std::fixed << std::setprecision(13);

	int n, k;
	std::cin >> n >> k;

	int c = 2E9;
	for (int i = 1; i <= k; i += 1) {
		int x;
		std::cin >> x ;
		c = std::min(x, c);
	}

	std::vector<int>strength(n);
	std::map<std::string, std::vector<int>>rec;
	for (int i = 1; i <= n; i += 1) {
		std::string s;
		std::cin >> strength[i] >> s;
		rec[s].push_back(strength[i]);
	}

	std::vector<int>all;
	for (auto& [x, v] : rec) {
		std::ranges::sort(v, std::greater());
		for (int i = 0; i < std::min(c, int(v.size())); i += 1) {
			all.push_back(v[i]);
		}
	}

	std::ranges::sort(all);
	for (int i = 1; i <= n; i += 1) {
		int pos = std::ranges::lower_bound(all, strength[i]) - all.begin();
		std::cout << all.size() - pos << '\n';
	}
	return 0;
}
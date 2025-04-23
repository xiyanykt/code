#include<bits/stdc++.h>

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

constexpr int Mod = 1E9 + 7;

constexpr int add(int x, int y) {
	return (i64(x) + y) % Mod;
}
constexpr int mul(int x, int y) {
	return (i64(x) * y) % Mod;
}
constexpr int del(int x, int y) {
	return (i64(x) + Mod - y) % Mod;
}

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout << std::fixed << std::setprecision(13);

	int q;
	std::cin >> q;

	int sum = 0;
	std::vector<int>stk;
	for (; q > 0; q -= 1) {
		int t, v;
		std::cin >> t >> v;
		for (; t > 0; t -= 1) {
			sum = del(sum, mul(stk.back(), stk.size()));
			stk.pop_back();
		}
		stk.push_back(v);
		sum = add(sum, mul(v, stk.size()));
		std::cout << sum << '\n';
	}

	return 0;
}
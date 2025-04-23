#include<bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f64 = long double;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

#ifndef ONLINE_JUDGE
#include "algo/debug.hpp"
#else
#define debug(...) (void)42
#endif

template<class T>
constexpr bool chmax(T& x, T y) {
	if (y > x) {
		x = y;
		return true;
	}
	return false;
}

template<class T>
constexpr bool chmin(T& x, T y) {
	if (y < x) {
		x = y;
		return true;
	}
	return false;
}

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::string s[8];
	std::array<int, 8> x {};
	for (int i = 0; i < 8; i += 1) {
		std::cin >> s[i] >> x[i];
	}

	int a = 0;
	if (x[1] > x[0]) {
		a += 1;
	}

	int b = 2;
	if (x[3] > x[2]) {
		b += 1;
	}

	int c = 4;
	if (x[5] > x[4]) {
		c += 1;
	}

	int d = 6;
	if (x[7] > x[6]) {
		d += 1;
	}

	int e = (x[a] > x[b] ? a : b);
	int f = (x[c] > x[d] ? c : d);
	if (x[e] > x[f]) {
		std::swap(e, f);
	}
	std::cout << std::format("{} beats {}", s[f], s[e]);
	return 0;
}
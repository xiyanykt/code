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

	system("gen.exe > 2.in");
	system("gen.exe > 3.in");
	system("gen.exe > 4.in");
	system("gen.exe > 5.in");
	system("gen.exe > 6.in");
	system("gen.exe > 7.in");

	system("std.exe < 2.in > 2.out");
	system("std.exe < 3.in > 3.out");
	system("std.exe < 4.in > 4.out");
	system("std.exe < 5.in > 5.out");
	system("std.exe < 6.in > 6.out");
	system("std.exe < 7.in > 7.out");
	return 0;
}
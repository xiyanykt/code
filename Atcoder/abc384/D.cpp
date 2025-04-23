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
	int n;
	i64 s;
	std::cin >> n >> s;

	i64 f = 0;
	std::vector<int>a(n + 1);
	for (int i = 1; i <= n; i += 1) {
		std::cin >> a[i];
		f += a[i];
	}

	a.insert(a.end(), a.begin() + 1, a.end());

	s %= f;

	i64 t = 0;
	std::set<i64>rec {0};
	for (int i = 1; i <= 2 * n; i += 1) {
		t += a[i];
		rec.insert(t);
	}

	t = 0;
	for (int i = 1; i <= 2 * n; i += 1) {
		t += a[i];
		if (rec.contains(s + t)) {
			std::cout << "Yes\n";
			return 0;
		}
	}
	std::cout << "No\n";
	return 0;
}
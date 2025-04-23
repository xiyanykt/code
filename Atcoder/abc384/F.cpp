#include<bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f64 = long double;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

#include"W:\v\algo\debug.hpp"

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
	std::cin >> n;

	std::vector<int>a(n + 1);
	for (int i = 1; i <= n; i += 1) {
		std::cin >> a[i];
	}

	constexpr int Kn = 27;
	i64 res = 0;
	for (int k = 1; k < Kn; k += 1) {
		int x = 1 << k;
		int y = x >> 1;
		// std::vector<i64>s(x);
		// std::vector<int>f(x);
		std::unordered_map<int, i64>s, f;
		for (int i = 1; i <= n; i += 1) {
			int r = a[i] % x;
			s[r] += a[i];
			f[r] += 1;
			res += (s[(y - r + x) % x] + i64(a[i]) * f[(y - r + x) % x]) >> (k - 1);
		}
	}

	std::cout << res << '\n';
	return 0;
}
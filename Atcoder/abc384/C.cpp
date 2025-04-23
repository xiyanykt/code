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

	constexpr int Kn = 5;
	std::vector<std::string>pool;
	std::string t = "ABCDE";

	std::array<int, Kn>c {};
	for (int k = 0; k < Kn; k += 1) {
		std::cin >> c[k];
	}

	for (int s = 0; s < (1 << Kn); s += 1) {
		std::string a = "";
		for (int i = 0; i < Kn; i += 1) {
			if (s >> i & 1) {
				a += t[i];
			}
		}
		if (!a.empty()) {
			pool.push_back(a);
		}
	}

	auto f = [&](const std::string & s) {
		int r = 0;
		int k = s.size();
		for (int i = 0; i < k; i += 1) {
			r += c[s[i] - 'A'];
		}
		return r;
	};

	std::sort(pool.begin(), pool.end(), [&](const std::string & a, const std::string & b) {
		if (f(a) == f(b)) {
			return a < b;
		}
		return f(a) > f(b);
	});

	for (const auto & x : pool) {
		std::cout << x << '\n';
	}

	return 0;
}
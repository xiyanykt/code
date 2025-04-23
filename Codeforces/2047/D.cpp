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
	std::cout << std::fixed << std::setprecision(13);

	auto solve = [&]() {
		int n;
		std::cin >> n;

		std::vector<int>p(n);
		for (auto & c : p) {
			std::cin >> c;
		}

		int x = 1E9;
		std::vector<int>v, r;
		std::multiset<int>s(p.begin(), p.end());
		for (const auto & c : p) {
			if (c <= x && c == *s.begin()) {
				v.push_back(c);
			} else {
				r.push_back(c + 1);
				chmin(x, c + 1);
			}
			s.extract(c);
		}

		std::ranges::sort(r);
		debug(v);
		debug(r);
		v.insert(v.end(), r.begin(), r.end());
		for (const auto & c : v) {
			std::cout << c << ' ';
		}
		std::cout << '\n';
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
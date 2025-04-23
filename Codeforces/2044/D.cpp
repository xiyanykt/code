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

		std::set<int>s;
		std::vector<int>a(n + 1);
		for (int i = 1; i <= n; i += 1) {
			std::cin >> a[i];
			s.insert(i);
		}

		for (int i = 1; i <= n; i += 1) {
			s.erase(a[i]);
		}

		std::vector<int>b(n + 1), c(n + 1);
		b[1] = a[1];
		c[a[1]] += 1;
		for (int i = 2; i <= n; i += 1) {
			if (!c[a[i]]) {
				b[i] = a[i];
			} else {
				assert(!s.empty());
				b[i] = *s.rbegin();
				s.erase(*s.rbegin());
			}
			c[a[i]] += 1;
		}

		for (int i = 1; i <= n; i += 1) {
			std::cout << b[i] << " \n"[i == n];
		}
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
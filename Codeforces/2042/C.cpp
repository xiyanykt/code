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
		int n, k;
		std::cin >> n >> k;

		std::string s;
		std::cin >> s;
		s = ' ' + s;

		std::vector<int>c(n + 1);
		for (int i = 1; i <= n; i += 1) {
			c[i] = c[i - 1] + (s[i] == '1' ? 1 : -1);
		}

		std::priority_queue<int, std::vector<int>, std::greater<>>q;
		for (int i = 1; i <= n - 1; i += 1) {
			q.push(c[i]);
		}

		i64 cur = 0;
		for (int m = 2; m <= n; m += 1) {
			cur -= q.top();
			q.pop();
			if (cur + 1LL * (m - 1) * c.back() >= k) {
				std::cout << m << '\n';
				return ;
			}
		}

		std::cout << -1 << '\n';
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
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
		int n, m, v;
		std::cin >> n >> m >> v;

		std::vector<int>a(n + 1);
		for (int i = 1; i <= n; i += 1) {
			std::cin >> a[i];
		}

		std::vector<i64>s(n + 1);
		for (int i = 1; i <= n; i += 1) {
			s[i] = s[i - 1] + a[i];
		}

		std::vector<int>next(m + 2), prev(m + 2);
		for (int i = 1, j = 1; i <= m; i += 1, j += 1) {
			while (j <= n and s[j] - s[next[i - 1]] < v) {
				j += 1;
			}
			next[i] = j;
		}
		prev.back() = n + 1;
		for (int i = m, j = n; i >= 1; i -= 1, j -= 1) {
			while (j >= 1 and s[prev[i + 1] - 1] - s[j - 1] < v) {
				j -= 1;
			}
			prev[i] = j;
		}

		debug(next, prev);

		i64 ans = -1;
		for (int i = 1; i <= m - 1; i += 1) {
			if (next[i] < prev[i + 1]) {
				chmax(ans, s[prev[i + 1] - 1] - s[next[i]]);
			}
		}
		if (prev[1] >= 1) {
			chmax(ans, s[prev[1] - 1]);
		}
		if (next[m] <= n) {
			chmax(ans, s[n] - s[next[m]]);
		}
		std::cout << ans << '\n';
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
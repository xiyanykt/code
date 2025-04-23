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
#define int i64
	auto solve = [&]() {
		int n, m, L;
		std::cin >> n >> m >> L;

		std::vector<int>l(n + 1), r(n + 1);
		for (int i = 1; i <= n; i += 1) {
			std::cin >> l[i] >> r[i];
		}

		std::vector<int>x(m + 1), v(m + 1);
		for (int i = 1; i <= m; i += 1) {
			std::cin >> x[i] >> v[i];
		}

		int cur = 1, cnt = 0;
		std::priority_queue<int>q;
		for (int i = 1, j = 1; i <= n; i += 1) {
			int t = r[i] - l[i] + 2;
			while (j <= m and x[j] < l[i]) {
				q.push(v[j]);
				j += 1;
			}
			while (not q.empty() and cur < t) {
				cur += q.top();
				cnt += 1;
				q.pop();
			}
			debug(cur, t);
			if (cur < t) {
				std::cout << -1 << '\n';
				return ;
			}
		}
		std::cout << cnt << '\n';
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
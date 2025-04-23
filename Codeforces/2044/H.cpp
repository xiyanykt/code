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
		int n, q;
		std::cin >> n >> q;

		std::vector<std::vector<int>>a(n + 1, std::vector<int>(n + 1));
		for (int i = 1; i <= n; i += 1) {
			for (int j = 1; j <= n; j += 1) {
				std::cin >> a[i][j];
			}
		}

		std::vector<std::vector<i64>>s1(n + 1, std::vector<i64>(n + 1)), s2(n + 1, std::vector<i64>(n + 1)), s3(n + 1, std::vector<i64>(n + 1));
		for (int i = 1; i <= n; i += 1) {
			for (int j = 1; j <= n; j += 1) {
				s1[i][j] += s1[i - 1][j] + s1[i][j - 1] - s1[i - 1][j - 1] + a[i][j];
				s2[i][j] += s2[i - 1][j] + s2[i][j - 1] - s2[i - 1][j - 1] + i64(a[i][j]) * i;
				s3[i][j] += s3[i - 1][j] + s3[i][j - 1] - s3[i - 1][j - 1] + i64(a[i][j]) * j;
			}
		}

		while (q--) {
			int x1, y1, x2, y2;
			std::cin >> x1 >> y1 >> x2 >> y2;

			auto ask = [&](const auto & M) {
				return M[x2][y2] - M[x2][y1 - 1] - M[x1 - 1][y2] + M[x1 - 1][y1 - 1];
			};

			int len = y2 - y1 + 1;
			i64 res = 0;
			res -= i64(x1) * len * ask(s1);
			res += ask(s3) - ask(s1) * (y1 - 1);
			res += ask(s2) * len;
			// for (int i = x1; i <= x2; i += 1) {
			// 	for (int j = y1; j <= y2; j += 1) {
			// 		res += i64(a[i][j]) * ((i - x1) * (y2 - y1 + 1) + j - y1 + 1);
			// 		res += a[i][j] * i * len;
			// 		res -= a[i][j] * x1 * len;
			// 		res += a[i][j] * (j - y1 + 1);
			// 	}
			// }
			std::cout << res << " \n"[!q];
		}
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
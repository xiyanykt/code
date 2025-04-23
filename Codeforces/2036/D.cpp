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
constexpr void chmax(T& x, T y) {
	if (y > x) {
		x = y;
	}
}

template<class T>
constexpr void chmin(T& x, T y) {
	if (y < x) {
		x = y;
	}
}

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout << std::fixed << std::setprecision(13);

	auto solve = [&]() {
		int n, m;
		std::cin >> n >> m;

		std::vector a(n + 1, std::vector<int>(m + 1));
		for (int i = 1; i <= n; i += 1) {
			std::string s;
			std::cin >> s;
			for (int j = 1; j <= m; j += 1) {
				a[i][j] = s[j - 1] - '0';
			}
		}

		int cnt = 0;
		for (int x = 1, y = 1; x <= n / 2 and y <= m / 2; x += 1, y += 1) {
			std::vector<int>t;
			int i = x, j = y;
			for (i = x, j = y; j <= m - y + 1; j += 1) {
				t.push_back(a[i][j]);
			}
			t.pop_back();
			j -= 1;
			for (; i <= n - x + 1; i += 1) {
				t.push_back(a[i][j]);
			}
			i -= 1;
			t.pop_back();
			for (; j >= y; j -= 1) {
				t.push_back(a[i][j]);
			}
			j += 1;
			t.pop_back();
			for (; i >= x; i -= 1) {
				t.push_back(a[i][j]);
			}
			t.pop_back();
			if (t.size() >= 4) {
				int m = t.size();
				for (int i = 0; i < m; i += 1) {
					if (t[i] == 1 and t[(i + 1) % m] == 5 and t[(i + 2) % m] == 4 and t[(i + 3) % m] == 3) {
						cnt += 1;
					}
				}
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
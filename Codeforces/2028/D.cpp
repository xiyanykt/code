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

		constexpr int Kn = 3;
		std::vector p(Kn + 1, std::vector<int>(n + 1));
		std::vector ord(Kn + 1, std::vector<int>(n + 1));
		for (int t = 1; t <= Kn; t += 1) {
			for (int i = 1; i <= n; i += 1) {
				std::cin >> p[t][i];
				ord[t][p[t][i]] = i;
			}
		}

		std::array<int, Kn>k {p[1][1], p[2][1], p[3][1]};

		std::vector<std::pair<int, int>>f(n + 1, std::pair(-1, -1));
		f[1] = {0, 0};
		for (int x = 2; x <= n; x += 1) {
			for (int t = 0; t < Kn; t += 1) {
				if (p[t + 1][x] < k[t]) {
					f[x] = {t, ord[t + 1][k[t]]};
				}
			}
			if (f[x].first != -1) {
				for (int t = 0; t < Kn; t += 1) {
					chmax(k[t], p[t + 1][x]);
				}
			}
		}

		if (f.back().first == -1) {
			std::cout << "NO\n";
			return ;
		}
		std::cout << "YES\n";

		std::vector<std::pair<int, int>>ans;
		for (int i = n; i >= 2;) {
			ans.push_back({f[i].first, i});
			i = f[i].second;
		}

		std::cout << ans.size() << '\n';
		for (const auto & [x, v] : ans | std::ranges::views::reverse) {
			std::cout << "qkj"[x] << ' ' << v << '\n';
		}
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
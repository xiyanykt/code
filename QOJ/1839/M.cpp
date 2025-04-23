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

		std::vector<int>b(n + 1);
		for (int i = 1; i <= n; i += 1) {
			std::cin >> b[i];
		}

		int g = 0;
		for (int i = 2; i <= n; i += 1) {
			g = std::gcd(g, b[i] - b[i - 1]);
		}

		if (g == 0) {
			std::cout << k << ' ' << i64(k) * (k + 1) / 2 << '\n';
			return ;
		}

		int cnt = 0;
		i64 sum = 0;
		int top = 0;
		std::vector<int>lsh(n + 1), rsh(n + 1), stk(n + 1);
		for (int i = 1; i <= n; i += 1) {
			int k = top;
			while (k > 0 && b[i] < b[stk[k]]) {
				k -= 1;
			}
			if (k > 0) {
				rsh[stk[k]] = i;
			}
			if (k < top) {
				lsh[i] = stk[k + 1];
			}
			stk[top = (k += 1)] = i;
		}

		auto work = [&](int x) {
			bool ok = true;
			auto dfs = [&](auto && dfs, int p, int l, int r) {
				if (p == 0) {
					return 0;
				}
				if (l == r) {
					return b[l] + x;
				}
				int u = dfs(dfs, lsh[p], l, p - 1);
				int v = dfs(dfs, rsh[p], p + 1, r);
				int g = std::gcd(b[p] + x, std::gcd(u, v));
				ok &= (g == (b[p] + x));
				return g;
			};
			dfs(dfs, stk[1], 1, n);
			return ok;
		};

		int m = *std::min_element(b.begin() + 1, b.end());
		for (int x = 1; x * x <= g; x += 1) {
			if (g % x == 0) {
				int h = x - m;
				if (h >= 1 && h <= k && work(h)) {
					cnt += 1;
					sum += h;
				}
				if (x * x != g) {
					int h = (g / x) - m;
					if (h >= 1 && h <= k && work(h)) {
						cnt += 1;
						sum += h;
					}
				}
			}
		}
		std::cout << cnt << ' ' << sum << '\n';
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
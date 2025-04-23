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

constexpr int Kn = 32;
constexpr i64 Kw = 1E9;
auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout << std::fixed << std::setprecision(13);

	auto solve = [&]() {
		int k, l1, r1, l2, r2;
		std::cin >> k >> l1 >> r1 >> l2 >> r2;

		i64 cnt = 0;
		for (i64 p = 1; p <= Kw; p *= k) {
			i64 lo = 1, hi = Kw;
			while (lo <= hi) {
				i64 mid = (lo + hi) >> 1;
				if (i128(mid) * p < l2) {
					lo = mid + 1;
				} else {
					hi = mid - 1;
				}
			}
			i64 u = lo;
			lo = 1, hi = Kw;
			while (lo <= hi) {
				i64 mid = (lo + hi) >> 1;
				if (i128(mid) * p <= r2) {
					lo = mid + 1;
				} else {
					hi = mid - 1;
				}
			}
			i64 v = lo - 1;
		}
	};

	auto bf = [&]() {
		i64 k, l1, r1, l2, r2;
		std::cin >> k >> l1 >> r1 >> l2 >> r2;

		// for (int z = 1; z <= Kw; z *= k) {
		// 	for (int x = l1; x <= r1; x += 1) {
		// 		for (int y = l2; y <= r2; y += 1) {
		// 			if (y >= x && y % x == 0 && y / x == z) {
		// 				debug(x, y);
		// 			}
		// 		}
		// 	}
		// }

		i64 cnt = 0;
		for (i64 p = 1; p <= Kw; p *= k) {
			i64 lo = 1, hi = Kw;
			while (lo <= hi) {
				i64 mid = (lo + hi) >> 1;
				if (i128(mid) * p < l2) {
					lo = mid + 1;
				} else {
					hi = mid - 1;
				}
			}
			i64 l = lo;
			lo = 1, hi = Kw;
			while (lo <= hi) {
				i64 mid = (lo + hi) >> 1;
				if (i128(mid) * p <= r2) {
					lo = mid + 1;
				} else {
					hi = mid - 1;
				}
			}
			i64 r = lo - 1;
			if (l <= r) {
				if (l > r1 || r < l1) {
					continue;
				}
				cnt += std::max(i64(0), std::min(r, r1) - std::max(l, l1) + 1);
			}
		}
		std::cout << cnt << '\n';
	};

	int t;
	std::cin >> t;
	while (t--) {
		// solve();
		bf();
	}
	return 0;
}
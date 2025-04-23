#include<bits/stdc++.h>

using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128_t;
using f128 = __float128;

#ifndef ONLINE_JUDGE
#include "algo\debug.hpp"
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

template<class T, const int M>
struct Basis {
	int cnt;
	std::array<T, M>a;
	std::array<T, M>t;

	Basis() {
		a.fill(0);
		t.fill(-1);
		cnt = 0;
	}

	bool add(T x, T y = std::numeric_limits<T>::max()) {
		for (int j = M - 1; j >= 0; j -= 1) {
			if (x >> j & 1) {
				if (not a[j]) {
					a[j] = x;
					t[j] = y;
					cnt += 1;
					return true;
				} else if (t[j] < y) {
					std::swap(t[j], y);
					std::swap(a[j], x);
				}
				x ^= a[j];
			}
		}
		return true;
	}

	T min(T x = std::numeric_limits<T>::max(), T l = {0}) {
		for (int j = M - 1; j >= 0; j -= 1) {
			if (a[j] and t[j] >= l) {
				x = std::min(x, x ^ a[j]);
			}
		}
		return x;
	}

	T max(T x = {0}, T l = {0}) {
		for (int j = M - 1; j >= 0; j -= 1) {
			if (a[j] and t[j] >= l) {
				x = std::max(x, x ^ a[j]);
			}
		}
		return x;
	}

	bool have(T x, T y = {0}) {
		for (int j = M - 1; j >= 0; j -= 1) {
			if (x >> j & 1 and t[j] >= y) {
				x ^= a[j];
			}
		}
		return x == 0;
	}
};

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout << std::fixed << std::setprecision(13);

	auto solve = [&]() {
		int n;
		std::cin >> n;

		std::vector<int>a(n + 1), b(n + 1);
		int sa = 0, sb = 0;
		for (int i = 1; i <= n; i += 1) {
			std::cin >> a[i];
			sa ^= a[i];
		}
		for (int i = 1; i <= n; i += 1) {
			std::cin >> b[i];
			sb ^= b[i];
		}

		Basis<int, 31>basis;
		for (int i = 1; i <= n; i += 1) {
			basis.add(a[i] ^ b[i]);
		}

		for (int i = 30; i >= 0; i -= 1) {
			int cur = std::max(sa, sb);
			int res = std::max(sa ^ basis.a[i], sb ^ basis.a[i]);
			if (cur > res) {
				sa ^= basis.a[i];
				sb ^= basis.a[i];
			}
		}

		std::cout << std::max(sa, sb) << '\n';
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
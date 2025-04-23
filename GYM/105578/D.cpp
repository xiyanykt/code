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

		std::vector<int>a(n), b(n), p(n);
		for (int i = 0; i < n; i += 1) {
			std::cin >> a[i];
			a[i] -= 1;
		}
		for (int i = 0; i < n; i += 1) {
			std::cin >> b[i];
			b[i] -= 1;
			p[b[i]] = a[i];
		}

		int parity = 0;
		std::vector<bool>vis(n);
		for (int i = 0; i < n; i += 1) {
			if (!vis[i]) {
				parity ^= 1;
				for (int j = i; !vis[j]; j = p[j]) {
					vis[j] = true;
					parity ^= 1;
				}
			}
		}

		std::cout << "BA"[parity];
		for (int i = 0; i < n - 1; i += 1) {
			char x;
			int l, r, d;
			std::cin >> x >> l >> r >> d;
			parity ^= (i64(d) * (r - l)) & 1;
			std::cout << "BA"[parity];
		}
		std::cout << '\n';
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
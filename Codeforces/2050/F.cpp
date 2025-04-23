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

template<typename T>
struct SparseTable {
	std::vector<std::vector<T>>jump;

	SparseTable() = default;
	constexpr SparseTable(const std::vector<T>& a, const T& val) {
		int n = a.size() - 1;
		int logn = std::__lg(n);
		jump.assign(logn + 2, std::vector<T>(n + 1, val));
		std::copy(a.begin(), a.end(), jump[0].begin());
		for (int j = 1; j <= logn + 1; j += 1) {
			for (int i = 1; i + (1 << (j - 1)) - 1 <= n; i += 1) {
				jump[j][i] = std::gcd(jump[j - 1][i], jump[j - 1][i + (1 << (j - 1))]);
			}
		}
	}

	constexpr T getRange(int l, int r) const {
		int k = std::__lg(r - l + 1);
		return std::gcd(jump[k][l], jump[k][r - (1 << k) + 1]);
	}
};

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
constexpr int Kn = 2E5;
u64 val[Kn + 1];

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	for (int x = 1; x <= Kn; x += 1) {
		val[x] = rng();
	}

	auto solve = [&]() {
		int n, q;
		std::cin >> n >> q;

		std::vector<int>a(n + 1);
		for (int i = 1; i <= n; i += 1) {
			std::cin >> a[i];
		}

		std::vector<int>d(n + 1);
		for (int i = 2; i <= n; i += 1) {
			d[i] = a[i] - a[i - 1];
		}

		auto f = SparseTable<int>(d, 0);
		while (q--) {
			int l, r;
			std::cin >> l >> r;
			int x = 0;
			if (l < r) {
				x = f.getRange(l + 1, r);
			}
			std::cout << x << " \n"[!q];
		}
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
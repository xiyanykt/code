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
struct Fenwick {
	int n;
	std::vector<T>a;

	Fenwick() {}
	Fenwick(int n) {
		this->n = n;
		a.assign(n + 1, T());
	}

	void add(int p, const T& x) {
		for (int i = p; i <= n; i += i & -i) {
			a[i] += x;
		}
	}

	T sum(int p) {
		T ans = T();
		for (int i = p; i > 0; i -= i & -i) {
			ans += a[i];
		}
		return ans;
	}

	T getRange(int l, int r) {
		return sum(r) - sum(l - 1);
	}

	int select(int k) {
		int x = 0;
		T cur = T();
		for (int i = std::__lg(n); ~i; i -= 1) {
			x += 1 << i;
			if (x >= n or cur + a[x] >= k) {
				x -= 1 << i;
			} else {
				cur = cur + a[x];
			}
		}
		return x + 1;
	}
};

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout << std::fixed << std::setprecision(13);

	auto solve = [&]() {
		int n;
		std::cin >> n;

		std::map<int, int>rec;
		for (int i = 1; i <= n; i += 1) {
			int x;
			std::cin >> x;
			rec[x] += 1;
		}
		int c = n;
		for (const auto & [x, v] : rec) {
			chmin(c, n - v);
		}
		std::cout << c << '\n';
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
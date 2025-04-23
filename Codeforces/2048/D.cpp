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

	Fenwick() {

	}

	Fenwick(int n) {
		this->n = n;
		a.assign(n + 1, T());
	}

	void add(int p, const T& x) {
		if (p >= 1 && p <= n) {
			for (int i = p; i <= n; i += i & -i) {
				a[i] += x;
			}
		}
	}

	T sum(int p) {
		T ans = T();
		if (p >= 1 && p <= n) {
			for (int i = p; i > 0; i -= i & -i) {
				ans += a[i];
			}
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
		int n, m;
		std::cin >> n >> m;

		std::vector<int>dx{ -1};
		std::vector<int>a(n + 1), b(m + 1);
		for (int i = 1; i <= n; i += 1) {
			std::cin >> a[i];
			dx.push_back(a[i]);
		}

		for (int i = 1; i <= m; i += 1) {
			std::cin >> b[i];
			dx.push_back(b[i]);
		}

		std::ranges::sort(dx);
		dx.erase(std::unique(dx.begin() + 1, dx.end()), dx.end());

		auto index = [&](int x) ->int {
			return std::ranges::lower_bound(dx, x) - dx.begin();
		};

		for (int i = 1; i <= n; i += 1) {
			a[i] = index(a[i]);
		}

		for (int i = 1; i <= m; i += 1) {
			b[i] = index(b[i]);
		}

		Fenwick<int>fena(n + m);
		for (int i = 1; i <= n; i += 1) {
			fena.add(a[i], 1);
		}

		std::vector<int>rk(m + 1);
		for (int i = 1; i <= m; i += 1) {
			if (a[1] >= b[i]) {
				rk[i] = 1;
			} else {
				rk[i] = 1 + fena.getRange(b[i], n + m);
			}
		}

		std::ranges::sort(rk);
		for (int k = 1; k <= m; k += 1) {
			i64 x = 0;
			for (int i = k; i <= m; i += k) {
				x += rk[i];
			}
			std::cout << x << " \n"[k == m];
		}
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
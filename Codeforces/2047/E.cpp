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

template<class T> struct Fenwick {
	int n;
	std::vector<T>a;

	Fenwick() {

	}

	Fenwick(const int & n) {
		this->n = n;
		a.assign(n + 1, T{});
	}

	void add(int p, const T & x) {
		for (int i = p; i <= n; i += i & -i) {
			a[i] += x;
		}
	}

	T sum(int p) {
		T res {};
		while (p >= 1) {
			res += a[p];
			p -= p & -p;
		}
		return res;
	}

	T getRange(int l, int r) {
		return sum(r) - sum(l - 1);
	}

	int select(int k) {
		int cur = 0;
		int x = 0;
		for (int i = std::__lg(n); ~i; i -= 1) {
			if (x + (1 << i) <= n && cur + a[x + (1 << i)] < k) {
				x += 1 << i;
				cur += a[x];
			}
		}
		return x + 1;
	}
};

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	auto solve = [&]() {
		int n;
		std::cin >> n;

		std::vector<int>x(n + 1), y(n + 1);
		for (int i = 1; i <= n; i += 1) {
			std::cin >> x[i] >> y[i];
		}

		auto dx = x, dy = y;
		std::sort(dx.begin() + 1, dx.end());
		std::sort(dy.begin() + 1, dy.end());
		dx.erase(std::unique(dx.begin() + 1, dx.end()), dx.end());
		dy.erase(std::unique(dy.begin() + 1, dy.end()), dy.end());
		for (int i = 1; i <= n; i += 1) {
			x[i] = std::lower_bound(dx.begin() + 1, dx.end(), x[i]) - dx.begin();
			y[i] = std::lower_bound(dy.begin() + 1, dy.end(), y[i]) - dy.begin();
		}

		int kx = dx.size() - 1, ky = dy.size() - 1;
		Fenwick<int>fl(ky), fr(ky);
		std::map<int, std::vector<int>>rec;
		for (int i = 1; i <= n; i += 1) {
			rec[x[i]].push_back(y[i]);
			fr.add(y[i], 1);
		}

		auto check = [&](int k) {
			int j = std::max(fl.select(k), fr.select(k));
			if (j >= ky) {
				return false;
			}
			return fl.getRange(j + 1, ky) >= k && fr.getRange(j + 1, ky) >= k;
		};

		int res = 0, a = 0, b = 0;
		for (const auto & [x, v] : rec) {
			int lo = 0, hi = n / 4;
			while (lo <= hi) {
				int mid = (lo + hi) >> 1;
				if (check(mid)) {
					lo = mid + 1;
				} else {
					hi = mid - 1;
				}
			}
			int j = lo - 1;
			int k = std::max(fl.select(j), fr.select(j));
			if (j > res) {
				res = j;
				a = dx[x];
				b = dy[k] + 1;
			}
			for (const auto & c : v) {
				fr.add(c, -1);
				fl.add(c, 1);
			}
		}
		std::cout << std::format("{}\n{} {}\n", res, a, b);
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}

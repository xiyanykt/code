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
	int n;
	std::cin >> n;

	std::vector<int>a(n + 1), b(n + 1);
	for (int i = 1; i <= n; i += 1) {
		std::cin >> a[i];
		a[i] += 1;
	}

	for (int i = 1; i <= n; i += 1) {
		std::cin >> b[i];
		b[i] += 1;
	}

	int q;
	std::cin >> q;
	std::vector<int>x(q + 1), y(q + 1);
	for (int i = 1; i <= q; i += 1) {
		std::cin >> x[i] >> y[i];
	}

	const int B = 1000;
	// const int B = std::sqrt(n);
	std::vector<int>ord(q + 1);
	std::iota(ord.begin(), ord.end(), 0);

	auto belong = [&](int i) {
		return i / B;
	};

	std::sort(ord.begin() + 1, ord.end(), [&](const int & i, const int & j) {
		if (belong(x[i]) != belong(x[j])) {
			return belong(x[i]) < belong(x[j]);
		} else if (belong(x[i]) & 1) {
			return y[i] > y[j];
		}
		return y[i] < y[j];
	});

	std::vector<int>d{0};
	d.insert(d.end(), a.begin() + 1, a.begin() + n + 1);
	d.insert(d.end(), b.begin() + 1, b.begin() + n + 1);
	std::ranges::sort(d);
	d.erase(std::unique(d.begin() + 1, d.end()), d.end());

	auto index = [&](int x) ->int {
		return std::ranges::lower_bound(d, x) - d.begin();
	};

	auto da = a, db = b;
	for (int i = 1; i <= n; i += 1) {
		da[i] = index(da[i]);
		db[i] = index(db[i]);
	}

	i64 cur = 0;
	i64 suma = 0, sumb = 0;
	Fenwick<int>ca(2 * n), cb(2 * n);
	Fenwick<i64>sa(2 * n), sb(2 * n);
	std::vector<i64>ans(q + 1);
	for (int j = 1, l = 0, r = 0; j <= q; j += 1) {
		int i = ord[j];
		while (l < x[i]) {
			l += 1;
			i64 c = cb.sum(da[l]);
			i64 s = sb.sum(da[l]);
			cur += (c * a[l] - s) + (sumb - s - i64(r - c) * a[l]);
			suma += a[l];
			ca.add(da[l], 1);
			sa.add(da[l], a[l]);
		}
		while (l > x[i]) {
			i64 c = cb.sum(da[l]);
			i64 s = sb.sum(da[l]);
			cur -= (c * a[l] - s) + (sumb - s - i64(r - c) * a[l]);
			suma -= a[l];
			ca.add(da[l], -1);
			sa.add(da[l], -a[l]);
			l -= 1;
		}
		while (r < y[i]) {
			r += 1;
			i64 c = ca.sum(db[r]);
			i64 s = sa.sum(db[r]);
			cur += (c * b[r] - s) + (suma - s - i64(l - c) * b[r]);
			sumb += b[r];
			cb.add(db[r], 1);
			sb.add(db[r], b[r]);
		}
		while (r > y[i]) {
			i64 c = ca.sum(db[r]);
			i64 s = sa.sum(db[r]);
			cur -= (c * b[r] - s) + (suma - s - i64(l - c) * b[r]);
			sumb -= b[r];
			cb.add(db[r], -1);
			sb.add(db[r], -b[r]);
			r -= 1;
		}
		ans[i] = cur;
	}

	for (int i = 1; i <= q; i += 1) {
		std::cout << ans[i] << "\n";
	}
	return 0;
}
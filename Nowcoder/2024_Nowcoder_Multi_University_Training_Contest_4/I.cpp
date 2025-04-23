#include<bits/stdc++.h>

using i64 = int64_t;

template<typename T>
struct Fenwick {
	int n;
	std::vector<T>a;

	Fenwick(const int n = 0): n(n), a(n + 1, T()) {}

	void add(int p, const T& x) {
		while (p <= n) {
			a[p] += x;
			p += p & -p;
		}
	}

	T sum(int p) {
		T res = T();
		while (p) {
			res += a[p];
			p -= p & -p;
		}
		return res;
	}

	T getRange(int l, int r) {
		return sum(r) - sum(l - 1);
	}

	int select(const T& k) {
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

#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) (void)42
#endif

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, m;
	std::cin >> n >> m;

	Fenwick<int>fen(n);

	std::map<int, std::vector<int>>rec;
	for (int i = 1; i <= m; i += 1) {
		int x, y;
		std::cin >> x >> y;
		rec[x].emplace_back(y);
		rec[y].emplace_back(x);
	}

	i64 ans = 0;
	i64 sum = 0;

	for (int l = 1, r = 1; r <= n; r += 1) {
		for (const auto & c : rec[r]) {
			if (c >= l and c <= r) {
				sum += 1;
			}
		}
		while (sum != 1LL * (r - l + 1) * (r - l) / 2) {
			for (const auto & c : rec[l]) {
				if (c >= l and c <= r) {
					sum -= 1;
				}
			}
			l += 1;
		}
		ans += r - l + 1;
	}

	std::cout << ans << "\n";

	return 0;
}
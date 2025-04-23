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

	auto solve = [&]() {
		int n;
		std::cin >> n;

		std::vector<int>a(n + 1);
		for (int i = 1; i <= n; i += 1) {
			std::cin >> a[i];
		}

		std::vector<int>p(n + 1);
		std::iota(p.begin(), p.end(), 0);
		std::ranges::sort(p, {}, [&](const auto & i) {
			return a[i];
		});

		i64 pre = 0;
		std::vector<int>ans(n + 1);
		for (int i = 1, j = 1; i <= n; i += 1) {
			if (i == j) {
				j += 1;
				pre += a[p[i]];
			}
			while (j <= n and pre >= a[p[j]]) {
				pre += a[p[j]];
				j += 1;
			}
			ans[p[i]] = j - 2;
		}

		for (int i = 1; i <= n; i += 1) {
			std::cout << ans[i] << " \n"[i == n];
		}
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
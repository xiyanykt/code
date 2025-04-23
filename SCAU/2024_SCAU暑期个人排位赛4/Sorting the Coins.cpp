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

	T rangeSum(int l, int r) {
		return sum(r) - sum(l - 1);
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

	int n;
	std::cin >> n;

	std::vector<int>p(n + 1);
	for (int i = 1; i <= n; i += 1) {
		std::cin >> p[i];
	}
	std::vector<int>ans(n + 1, 1), v(n + 1);

	Fenwick<int>fen(n);

	int j = n;
	for (int i = 1; i <= n; i += 1) {
		fen.add(p[i], 1);
		v[p[i]] += 1;
		while (v[j]) {
			j -= 1;
		}
		if (j >= 1) {
			ans[i] = fen.rangeSum(1, j) + 1;
		}
	}

	for (int i = 0; i <= n; i += 1) {
		std::cout << ans[i] << " ";
	}

	return 0;
}
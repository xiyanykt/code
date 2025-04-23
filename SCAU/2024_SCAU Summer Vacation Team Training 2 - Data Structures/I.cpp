#include<bits/stdc++.h>

using i64 = int64_t;

struct DSU {
	std::vector<int>fa, sz;
	DSU() {}

	DSU(int n) {
		fa.resize(n + 1);
		std::iota(fa.begin(), fa.end(), 0);
		sz.assign(n + 1, 1);
	}

	int find(int x) {
		return x == fa[x] ? x : fa[x] = find(fa[x]);
	}

	bool same(int x, int y) {
		return find(x) == find(y);
	}

	bool merge(int x, int y) {
		x = find(x), y = find(y);
		if (x == y)return false;
		if (sz[x] < sz[y])std::swap(x, y);
		sz[x] += sz[y];
		fa[y] = x;
		return true;
	}

	int size(int x) {
		return sz[find(x)];
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

	std::cout << ([]() {
		int n, m;
		std::cin >> n >> m;

		std::vector<int>a(m + 1), b(m + 1);
		for (int i = 1; i <= m; i += 1) {
			std::cin >> a[i];
		}
		for (int i = 1; i <= m; i += 1) {
			std::cin >> b[i];
		}

		DSU dsu(2 * n);
		for (int i = 1; i <= m; i += 1) {
			if (dsu.same(a[i], b[i])) {
				return false;
			}
			dsu.merge(a[i], b[i] + n);
			dsu.merge(b[i], a[i] + n);
		}

		return true;
	}() ? "Yes\n" : "No\n");
	return 0;
}
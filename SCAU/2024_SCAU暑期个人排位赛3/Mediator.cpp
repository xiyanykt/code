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

constexpr int MOD = 998244353;
constexpr int N = 1E5;
constexpr int limits = 1E4;

int vis[N + 1];

std::bitset<limits>B[N + 1];
std::vector<int>G[N + 1];

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, q;
	std::cin >> n >> q;

	i64 x = 0;
	while (q--) {
		i64 a, b, c;
		std::cin >> a >> b >> c;
		a = 1 + ((a * (x + 1)) % MOD) % 2;
		b = 1 + ((b * (x + 1)) % MOD) % n;
		c = 1 + ((c * (x + 1)) % MOD) % n;
		if (a == 1) {
			if (c >= limits) {
				G[b].push_back(c);
			} else {
				B[b].set(c);
			}
			if (b >= limits) {
				G[c].push_back(b);
			} else {
				B[c].set(b);
			}
		} else {
			auto y = B[b] & B[c];
			if (y.count()) {
				x = y._Find_first();
			} else {
				x = 0;
				for (const auto & u : G[b]) {
					vis[u] = 1;
				}
				for (const auto & v : G[c]) {
					if (vis[v]) {
						x = v;
						break;
					}
				}
				for (const auto & u : G[b]) {
					vis[u] = 0;
				}
			}
			std::cout << x << "\n";
		}
	}

	return 0;
}
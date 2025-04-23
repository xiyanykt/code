#include<bits/stdc++.h>

using i64 = int64_t;

template<class Info>
struct SegmentTree {
	int n;
	std::vector<Info>info;

	SegmentTree() {}

	SegmentTree(int n) {
		this->n = n;
		info.assign(4 << std::__lg(n), Info());
	}

	template<typename T>
	void build(const std::vector<T>& a) {
		auto work = [&](auto && self, int p, int l, int r) {
			if (l == r) {
				info[p] = Info(a[l]);
				return;
			}
			int mid = std::midpoint(l, r);
			self(self, p << 1, l, mid), self(self, p << 1 | 1, mid + 1, r);
			info[p] = info[p << 1] + info[p << 1 | 1];
		};
		work(work, 1, 1, n);
	}

	void modify(int p, int l, int r, int L, int R, const Info& v) {
		if (l > R or r < L) {
			return;
		}
		if (L <= l and r <= R) {
			info[p] = v;
			return;
		}
		int mid = std::midpoint(l, r);
		modify(p << 1, l, mid, L, R, v), modify(p << 1 | 1, mid + 1, r, L, R, v);
		info[p] = info[p << 1] + info[p << 1 | 1];
	}
	void modify(int p, const Info& v) {
		modify(1, 1, n, p, p, v);
	}

	Info rangeQuery(int p, int l, int r, int L, int R) {
		if (l > R or r < L) {
			return Info();
		}
		if (L <= l and r <= R) {
			return info[p];
		}
		int mid = std::midpoint(l, r);
		return rangeQuery(p << 1, l, mid, L, R) + rangeQuery(p << 1 | 1, mid + 1, r, L, R);
	}
	Info rangeQuery(int l, int r) {
		return rangeQuery(1, 1, n, l, r);
	}

	template<class F>
	int findFirst(int p, int l, int r, int L, int R, F pred) {
		if (l > R or r < L or not pred(info[p])) {
			return -1;
		}
		if (l == r) {
			return l;
		}
		int mid = std::midpoint(l, r);
		int res = findFirst(p << 1, l, mid, L, R, pred);
		return res == -1 ? findFirst(p << 1 | 1, mid + 1, r, L, R, pred) : res;
	}
	template<class F>
	int findFirst(int l, int r, F pred) {
		return findFirst(1, 1, n, l, r, pred);
	}

	template<class F>
	int findLast(int p, int l, int r, int L, int R, F pred) {
		if (l > R or r < L or not pred(info[p])) {
			return -1;
		}
		if (l == r) {
			return r;
		}
		int mid = std::midpoint(l, r);
		int res = findLast(p << 1 | 1, mid + 1, r, L, R, pred);
		return res == -1 ? findLast(p << 1, l, mid, L, R, pred) : res;
	}
	template<class F>
	int findLast(int l, int r, F pred) {
		return findLast(1, 1, n, l, r, pred);
	}
};

constexpr int inf = 1E9;

struct Info {
	int val = 0;
};
Info operator+(const Info& a, const Info& b) {
	return {std::max(a.val, b.val)};
}

#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) (void)42
#endif

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	auto solve = [&]() {
		int n, k;
		std::cin >> n >> k;

		std::vector<int>dis(2 * n + 1);

		std::vector<int>w(n + 1);
		for (int i = 1; i <= n; i += 1) {
			std::cin >> w[i];
			dis[i] = w[i];
			dis[i + n] = w[i] + k;
		}

		std::vector adj(n + 1, std::vector<int>());
		for (int i = 1; i <= n - 1; i += 1) {
			int u, v;
			std::cin >> u >> v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}

		std::ranges::sort(dis);

		auto Des = [&](int x)->int{
			return std::ranges::lower_bound(dis, x) - dis.begin();
		};

		SegmentTree<Info>seg(2 * n);
		
		std::vector f(2 * n + 1, std::vector<int>(1, 0));
		
		std::vector<int>ans(n + 1), con(n + 1);
		
		auto dfs = [&](auto && self, int u, int par, int dep)->void {
			auto y = Des(w[u]);
			auto x = Des(w[u] + k);
			auto j = seg.rangeQuery(x + 1, 2 * n);
			con[dep] = u;
			ans[u] = con[j.val];
			f[y].push_back(dep);
			seg.modify(y, {f[y].back()});
			for (const auto & v : adj[u]) {
				if (v == par) {
					continue;
				}
				self(self, v, u, dep + 1);
			}
			f[y].pop_back();
			seg.modify(y, {f[y].back()});
		};

		dfs(dfs, 1, 0, 1);

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

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
	i64 val = 0;
};
Info operator+(const Info& a, const Info& b) {
	return {std::max(a.val, b.val)};
}

using f64 = long double;

#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) (void)42
#endif

constexpr f64 P = acos(-1);

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cout << std::fixed << std::setprecision(13);

	int n;
	std::cin >> n;

	std::vector<int>r(n + 1), h(n + 1);
	for (int i = 1; i <= n; i += 1) {
		std::cin >> r[i] >> h[i];
	}

	std::vector<i64>dis(n + 1);
	for (int i = 1; i <= n; i += 1) {
		dis[i] = 1LL * r[i] * r[i] * h[i];
	}

	std::ranges::sort(dis);
	dis.erase(std::unique(dis.begin() + 1, dis.end()), dis.end());

	auto Des = [&](i64 x) {
		return std::ranges::lower_bound(dis, x) - dis.begin();
	};

	SegmentTree<Info>seg(n);
	std::vector<i64>dp(n + 1);
	for (int i = 1; i <= n; i += 1) {
		i64 v = 1LL * r[i] * r[i] * h[i];
		auto j = Des(v);
		auto u = seg.rangeQuery(1, j - 1);
		dp[i] = v + u.val;
		seg.modify(j, {std::max(seg.rangeQuery(j, j).val, dp[i])});
	}

	f64 ans = *std::ranges::max_element(dp);
	ans *= P;
	std::cout << ans << "\n";
	return 0;
}
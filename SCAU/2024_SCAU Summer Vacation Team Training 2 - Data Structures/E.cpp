#include<bits/stdc++.h>

using i64 = int64_t;

#define int i64

constexpr int N = 2E5;

int a[N + 1];

template<class Info, class Tag>
struct LazySegmentTree {
	int n;
	std::vector<Info>info;
	std::vector<Tag>tag;

	LazySegmentTree () {}
	LazySegmentTree (int n) {
		this->n = n;
		info.assign(4 << std::__lg(n), Info()), tag.assign(4 << std::__lg(n), Tag());
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

	void apply(int p, const Tag& v) {
		info[p].apply(v), tag[p].apply(v);
	}
	void pull(int p) {
		apply(p << 1, tag[p]), apply(p << 1 | 1, tag[p]);
		tag[p] = Tag();
	}

	void modify(int p, int l, int r, int L, int R, const Info& v) {
		if (l > R or r < L) {
			return;
		}
		if (L <= l and r <= R) {
			info[p] = v;
			return;
		}
		pull(p);
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
		// pull(p);
		int mid = std::midpoint(l, r);
		return rangeQuery(p << 1, l, mid, L, R) + rangeQuery(p << 1 | 1, mid + 1, r, L, R);
	}
	Info rangeQuery(int l, int r) {
		return rangeQuery(1, 1, n, l, r);
	}

	void rangeApply(int p, int l, int r, int L, int R, const Tag& v) {
		if (l > R or r < L or info[p].val <= 1) {
			return;
		}
		if (l == r) {
			i64 v = std::sqrt(a[l]);
			info[p].sum -= a[l];
			info[p].sum += v;
			info[p].val = v;
			a[l] = v;
			return;
		}
		int mid = std::midpoint(l, r);
		rangeApply(p << 1, l, mid, L, R, v), rangeApply(p << 1 | 1, mid + 1, r, L, R, v);
		info[p] = info[p << 1] + info[p << 1 | 1];
	}
	void rangeApply(int l, int r, const Tag& v) {
		rangeApply(1, 1, n, l, r, v);
	}
};

constexpr i64 inf = 1E18;

struct Tag {
	i64 add = 0;
	void apply(const Tag& t) {
		add += t.add;
	}
};
struct Info {
	i64 val = 0;
	i64 sum = 0;
	void apply(const Tag& t) {

	}
};
Info operator+(const Info& a, const Info& b) {
	return {std::max(a.val, b.val), a.sum + b.sum};
}

#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) (void)42
#endif

signed main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n;
	std::cin >> n;

	for (int i = 1; i <= n; i += 1) {
		std::cin >> a[i];
	}

	LazySegmentTree<Info, Tag>seg(n);
	for (int i = 1; i <= n; i += 1) {
		seg.modify(i, {a[i], a[i]});
	}

	for (int i = 1; i <= n; i += 1) {
		int o, l, r, c;
		std::cin >> o >> l >> r >> c;
		if (o == 0) {
			seg.rangeApply(l, r, {});
		} else {
			std::cout << (seg.rangeQuery(l, r).sum) << "\n";
		}
	}

	return 0;
}
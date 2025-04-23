#include<bits/stdc++.h>

using i64 = int64_t;

#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) (void)42
#endif

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
			int mid = l + r >> 1;
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
		int mid = l + r >> 1;
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
		pull(p);
		int mid = l + r >> 1;
		return rangeQuery(p << 1, l, mid, L, R) + rangeQuery(p << 1 | 1, mid + 1, r, L, R);
	}
	Info rangeQuery(int l, int r) {
		return rangeQuery(1, 1, n, l, r);
	}

	void rangeApply(int p, int l, int r, int L, int R, const Tag& v) {
		if (l > R or r < L) {
			return;
		}
		if (L <= l and r <= R) {
			apply(p, v);
			return;
		}
		pull(p);
		int mid = l + r >> 1;
		rangeApply(p << 1, l, mid, L, R, v), rangeApply(p << 1 | 1, mid + 1, r, L, R, v);
		info[p] = info[p << 1] + info[p << 1 | 1];
	}
	void rangeApply(int l, int r, const Tag& v) {
		rangeApply(1, 1, n, l, r, v);
	}

	template<class F>
	int findFirst(int p, int l, int r, int L, int R, F pred) {
		if (l > R or r < L or not pred(info[p])) {
			return -1;
		}
		if (l == r) {
			return l;
		}
		pull(p);
		int mid = l + r >> 1;
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
			return l;
		}
		pull(p);
		int mid = l + r >> 1;
		int res = findLast(p << 1 | 1, mid + 1, r, L, R, pred);
		return res == -1 ? findLast(p << 1, l, mid, L, R, pred) : res;
	}
	template<class F>
	int findLast(int l, int r, F pred) {
		return findLast(1, 1, n, l, r, pred);
	}
};

constexpr i64 inf = 1E18;

struct Tag {
	int add = 0;
	void apply(const Tag& t) {
		add += t.add;
	}
};
struct Info {
	int len = 0;
	int val = 0;
	void apply(const Tag& t) {
		val += len * t.add;
	}
};
Info operator+(const Info& a, const Info& b) {
	return {a.len + b.len, a.val + b.val};
}

struct Node {
	mutable int val = 0;

	friend constexpr bool operator<(const auto & lsh, const auto & rsh) {
		return lsh.val < rsh.val;
	}

};

int32_t main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cout << ([]() {
		int n, L, R;
		std::cin >> n >> L >> R;

		if (R == n) {
			return true;
		}

		i64 Q = 0;
		int S = (n - R + (R - L - 1)) / (R - L);
		for (int i = 1; i <= n; i += 1) {
			int h;
			std::cin >> h;
			Q += std::min(S, (h - 1) / 2);
		}
		return Q >= 1LL * S * L;
	}() ? "Yes\n" : "No\n");

	return 0;
}

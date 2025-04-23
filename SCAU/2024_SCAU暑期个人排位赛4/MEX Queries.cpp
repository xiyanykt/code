#include<bits/stdc++.h>

using i64 = int64_t;

template<class Info, class Tag>
struct LazySegmentTree {
	int n;
	std::vector<Info>info;
	std::vector<Tag>tag;

	LazySegmentTree () {}
	LazySegmentTree (int n) {
		this->n = n;
		info.assign(4 << std::__lg(n + 1), Info()), tag.assign(4 << std::__lg(n + 1), Tag());
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
		pull(p);
		int mid = std::midpoint(l, r);
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
		int mid = std::midpoint(l, r);
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
			return l;
		}
		pull(p);
		int mid = std::midpoint(l, r);
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
	int rev = 0;
	i64 add = -1;
	void apply(const Tag& t) {
		if (t.add != -1) {
			add = t.add;
			rev = 0;
		}
		if (t.rev) {
			rev ^= 1;
		}
	}
};
struct Info {
	i64 val = 0, len = 0;
	void apply(const Tag& t) {
		if (t.add != -1) {
			val = len * t.add;
		}
		if (t.rev) {
			val = len - val;
		}
	}
};
Info operator+(const Info& a, const Info& b) {
	return {a.val + b.val, a.len + b.len};
}

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

	std::vector<i64>dis(4 * n + 1);
	dis[0] = 1;
	std::vector<std::array<i64, 3>>qry(n);
	for (int i = 0, j = 1; i < n; i += 1) {
		i64 op, l, r;
		std::cin >> op >> l >> r;
		qry[i] = {op, l, r};
		dis[j++] = l, dis[j++] = l + 1, dis[j++] = r, dis[j++] = r + 1;
	}

	std::ranges::sort(dis);
	dis.erase(std::unique(dis.begin(), dis.end()), dis.end());

	// for (const auto & v : dis) {
	// 	std::cerr << v << " \n"[v == dis.back()];
	// }

	auto Des = [&](i64 x)->int{
		return std::ranges::lower_bound(dis, x) - dis.begin() + 1;
	};

	const int N = 4 * n + 1;
	LazySegmentTree<Info, Tag>seg(N);
	seg.build(std::vector<Info>(N + 1, {0, 1}));

	for (auto & [op, l, r] : qry) {
		l = Des(l), r = Des(r);
		if (op == 1) {
			seg.rangeApply(l, r, {0, 1});
		} else if (op == 2) {
			seg.rangeApply(l, r, {0, 0});
		} else {
			seg.rangeApply(l, r, {1, -1});
		}
		auto y = seg.findFirst(1, N, [&](const auto & u) {
			return u.val != u.len;
		});
		// std::cerr << y << "\n";
		std::cout << dis[y - 1] << "\n";
	}

	return 0;
}
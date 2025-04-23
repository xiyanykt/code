#include<bits/stdc++.h>

using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;

#ifndef ONLINE_JUDGE
#include "algo\debug.hpp"
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

	void build(const auto& a) {
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

constexpr int inf = 1E9;

struct Tag {
	int add = 0;
	void apply(const Tag& t) {
		add += t.add;
	}
};
struct Info {
	int cnt = 0;
	int val = inf;
	void apply(const Tag& t) {
		val += t.add;
	}
};
Info operator+(const Info& a, const Info& b) {
	if (a.val == b.val) {
		return {a.cnt + b.cnt, a.val};
	}
	if (a.val < b.val) {
		return a;
	}
	return b;
}

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cout << std::fixed << std::setprecision(13);

	auto solve = [&]() {
		int n, k;
		std::cin >> n >> k;

		std::vector<int>a(n + 1);
		for (int i = 1; i <= n; i += 1) {
			std::cin >> a[i];
		}

		LazySegmentTree<Info, Tag>seg(n);
		seg.build(std::vector<Info>(n + 1, {1, 0}));

		i64 ans = 0;
		std::map<int, std::vector<int>>vec;
		for (int i = 1; i <= n; i += 1) {
			vec[a[i]].push_back(i);
		}

		std::vector<int>nxt(n + 1), l(n + 1, n + 1), r(n + 1, n + 1);
		for (int i = 1; i <= n; i += 1) {
			auto& pos = vec[a[i]];
			int t = std::lower_bound(pos.begin(), pos.end(), i) - pos.begin();
			if (t + 1 < (int)pos.size()) {
				nxt[i] = pos[t + 1];
			}
			if (t + k < (int)pos.size()) {
				r[i] = pos[t + k];
			}
			if (t + k - 1 < (int)pos.size()) {
				l[i] = pos[t + k - 1];
			}
		}

		auto find = [&](const auto & v) {
			return (v.val == 0) * v.cnt;
		};

		for (int i = n; i >= 1; i -= 1) {
			if (nxt[i]) {
				seg.rangeApply(nxt[i], l[nxt[i]] - 1, { -1});
				seg.rangeApply(r[nxt[i]], n, { -1});
			}
			seg.rangeApply(i, l[i] - 1, {1});
			seg.rangeApply(r[i], n, {1});
			ans += find(seg.rangeQuery(i, n));
		}

		std::cout << ans << "\n";
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
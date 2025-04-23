#include<bits/stdc++.h>

using i64 = int64_t;

struct PresidentTree {

	struct Node {
		int ls, rs, val;
	};

	int n;
	int cnt;
	std::vector<Node>info;

	PresidentTree() {}
	PresidentTree(int n) {
		this->n = n;
		cnt = 0;
		info.resize(n << 5);
	}

	void push(int p) {
		info[p].val = info[info[p].ls].val + info[info[p].rs].val;
	}

	//root root [V] x
	void update(int& now, int pre, int l, int r, int pos) {
		info[now = ++cnt] = info[pre];
		if (l == r) {
			info[now].val += 1;
			return;
		}
		int mid = std::midpoint(l, r);
		if (pos <= mid) {
			update(info[now].ls, info[pre].ls, l, mid, pos);
		} else {
			update(info[now].rs, info[pre].rs, mid + 1, r, pos);
		}
		push(now);
	}

	//root root [V] [L,R]
	int getRange(int k, int p, int l, int r, int L, int R) {
		if (l > R or r < L) {
			return 0;
		}
		if (L <= l and r <= R) {
			return info[p].val - info[k].val;
		}
		int mid = std::midpoint(l, r);
		return getRange(info[k].ls, info[p].ls, l, mid, L, R) + getRange(info[k].rs, info[p].rs, mid + 1, r, L, R);
	}

	//root root kth [V]
	int getKthMax(int l, int r, int k, int L, int R) {
		if (info[r].val - info[l].val < k) {
			return 0;
		}
		if (L == R) {
			return L;
		}
		int mid = std::midpoint(L, R);
		int x = info[info[r].rs].val - info[info[l].rs].val;
		return k <= x ? getKthMax(info[l].rs, info[r].rs, k, mid + 1, R) : getKthMax(info[l].ls, info[r].ls, k - x, L, mid);
	}

	//root root kth [V]
	int getKthMin(int l, int r, int k, int L, int R) {
		if (info[r].val - info[l].val < k) {
			return 0;
		}
		if (L == R) {
			return L;
		}
		int mid = std::midpoint(L, R);
		int x = info[info[r].ls].val - info[info[l].ls].val;
		return k <= x ? getKthMin(info[l].ls, info[r].ls, k, L, mid) : getKthMin(info[l].rs, info[r].rs, k - x, mid + 1, R);
	}
};

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
	int add = 0;
	void apply(const Tag& t) {
		add += t.add;
	}
};
struct Info {
	int len = 0;
	int val = 0;
	void apply(const Tag& t) {
		val += t.add * len;
	}
};
Info operator+(const Info& a, const Info& b) {
	return {a.len + b.len, a.val + b.val};
}

#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) (void)42
#endif

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, q;
	std::cin >> n >> q;

	std::vector<int>l(q + 1), r(q + 1);
	for (int i = 1; i <= q; i += 1) {
		std::cin >> l[i] >> r[i];
	}

	int ans = 0;

	for (int i = 1; i <= q; i += 1) {
		std::vector<int>a(n + 1);
		for (int j = 1; j <= q; j += 1) {
			if (i == j) {
				continue;
			}
			a[l[j]] += 1;
			if (r[j] <= n - 1) {
				a[r[j] + 1] -= 1;
			}
		}
		for (int j = 1; j <= n; j += 1) {
			a[j] += a[j - 1];
		}
		int clz = 0;
		std::vector<int>s(n + 1);
		for (int j = 1; j <= n; j += 1) {
			s[j] = s[j - 1] + (a[j] == 1);
			clz += !!a[j];
		}
		for (int j = i + 1; j <= q; j += 1) {
			ans = std::max(ans, clz - (s[r[j]] - s[l[j] - 1]));
		}
	}

	std::cout << ans << "\n";

	return 0;
}
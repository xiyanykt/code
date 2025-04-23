#include<bits/stdc++.h>
using i64 = long long;

#ifndef ONLINE_JUDGE
#include "algo/debug.hpp"
#else
#define debug(...) (void)42
#endif

#define x first
#define y second

template<class T>
constexpr bool chmin(T& x, const T& y) {
	if (x > y) {
		x = y;
		return true;
	}
	return false;
}

template<class Info>
struct SegmentTree {
	int n;
	std::vector<Info>info;

	SegmentTree(const int & n) {
		this->n = n;
		info.assign(4 << std::__lg(n), Info());
	}

	SegmentTree(const std::vector<Info>& a) {
		int n = a.size() - 1;
		this->n = n;
		info.assign(4 << std::__lg(n), Info());
		auto work = [&](auto && self, int p, int l, int r) {
			if (l == r) {
				info[p] = Info(a[l]);
				return;
			}
			int mid = (l + r) >> 1;
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
		int mid = (l + r) >> 1;
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
		int mid = (l + r) >> 1;
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
		int mid = (l + r) >> 1;
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
		int mid = (l + r) >> 1;
		int res = findLast(p << 1 | 1, mid + 1, r, L, R, pred);
		return res == -1 ? findLast(p << 1, l, mid, L, R, pred) : res;
	}
	template<class F>
	int findLast(int l, int r, F pred) {
		return findLast(1, 1, n, l, r, pred);
	}

	template<class F>
	int findPrefixFirst(int p, int l, int r, int L, int R, const F& pred, Info& pref) {
		if (l > R or r < L) {
			return r + 1;
		}
		if (L <= l and r <= R) {
			if (not pred(pref + info[p])) {
				pref = pref + info[p];
				return r + 1;
			}
			if (l == r) {
				return l;
			}
			int mid = (l + r) >> 1;
			int res;
			if (pred(pref + info[p << 1])) {
				res = findPrefixFirst(p << 1, l, mid, L, R, pred, pref);
			} else {
				pref = pref + info[p << 1];
				res = findPrefixFirst(p << 1 | 1, mid + 1, r, L, R, pred, pref);
			}
			return res;
		}
		int mid = (l + r) >> 1;
		int res = mid + 1;
		if (L <= mid) {
			res = findPrefixFirst(p << 1, l, mid, L, R, pred, pref);
		}
		if (res == mid + 1 and mid + 1 <= R) {
			res = findPrefixFirst(p << 1 | 1, mid + 1, r, L, R, pred, pref);
		}
		return res;
	}
	template<class F>
	int findPrefixFirst(int l, int r, const F& pred) {
		Info pref = Info();
		int res = findPrefixFirst(1, 1, n, l, r, pred, pref);
		return res == r + 1 ? -1 : res;
	}

	template<class F>
	int findSurfixLast(int p, int l, int r, int L, int R, const F& pred, Info& surf) {
		if (l > R or r < L) {
			return l - 1;
		}
		if (L <= l and r <= R) {
			if (not pred(surf + info[p])) {
				surf = surf + info[p];
				return l - 1;
			}
			if (l == r) {
				return r;
			}
			int mid = (l + r) >> 1;
			int res;
			if (pred(surf + info[p << 1 | 1])) {
				res = findSurfixLast(p << 1 | 1, mid + 1, r, L, R, pred, surf);
			} else {
				surf = surf + info[p << 1 | 1];
				res = findSurfixLast(p << 1, l, mid, L, R, pred, surf);
			}
			return res;
		}
		int mid = (l + r) >> 1;
		int res = mid;
		if (mid + 1 <= R) {
			res = findSurfixLast(p << 1 | 1, mid + 1, r, L, R, pred, surf);
		}
		if (L <= mid and res == mid) {
			res = findSurfixLast(p << 1, l, mid, L, R, pred, surf);
		}
		return res;
	}
	template<class F>
	int findSurfixLast(int l, int r, const F& pred) {
		Info surf = Info();
		int res = findSurfixLast(1, 1, n, l, r, pred, surf);
		return res == l - 1 ? -1 : res;
	}
};

constexpr int inf = 1E9;
struct Max {
	int val = 0;
};

Max operator+(const Max & a, const Max & b) {
	return {std::max(a.val, b.val)};
}

struct Min {
	int val = inf;
};

Min operator+(const Min & a, const Min & b) {
	return {std::min(a.val, b.val)};
}

#define println(...) std::cout << std::format(__VA_ARGS__)

void solve() {
	int n;
	std::cin >> n;

	std::vector<int>l(n + 1), r(n + 1);
	for (int i = 1; i <= n; i += 1) {
		std::cin >> l[i] >> r[i];
	}

	auto fl = l, fr = r;
	std::ranges::sort(fl);
	std::ranges::sort(fr);
	fl.erase(std::unique(fl.begin() + 1, fl.end()), fl.end());
	fr.erase(std::unique(fr.begin() + 1, fr.end()), fr.end());

	auto dl = l, dr = r;
	for (int i = 1; i <= n; i += 1) {
		dl[i] = std::ranges::lower_bound(fl, dl[i]) - fl.begin();
		dr[i] = std::ranges::lower_bound(fr, dr[i]) - fr.begin();
	}

	int kl = dl.size() - 1, kr = dr.size() - 1;
	std::vector<std::multiset<int>>cl(kl + 1), cr(kr + 1);
	for (int i = 1; i <= n; i += 1) {
		cl[dl[i]].insert(r[i]);
		cr[dr[i]].insert(l[i]);
	}

	SegmentTree<Max>segl(kl);
	SegmentTree<Min>segr(kr);
	for (int i = 1; i <= n; i += 1) {
		segl.modify(dl[i], {*cl[dl[i]].rbegin()});
		segr.modify(dr[i], {*cr[dr[i]].begin()});
	}

	for (int i = 1; i <= n; i += 1) {
		cl[dl[i]].extract(r[i]);
		cr[dr[i]].extract(l[i]);
		if (!cl[dl[i]].empty()) {
			segl.modify(dl[i], {*cl[dl[i]].rbegin()});
		} else {
			segl.modify(dl[i], {});
		}
		if (!cr[dr[i]].empty()) {
			segr.modify(dr[i], {*cr[dr[i]].begin()});
		} else {
			segr.modify(dr[i], {});
		}

		int d = 0;
		int j = segl.findLast(1, dl[i], [&](const auto & u) {
			return u.val >= r[i];
		});
		int k = segr.findFirst(dr[i], kr, [&](const auto & u) {
			return u.val <= l[i];
		});
		if (j != -1) {
			d += l[i] - fl[j];
		}
		if (k != -1) {
			d += fr[k] - r[i];
		}
		println("{}\n", d);
		cl[dl[i]].insert(r[i]);
		cr[dr[i]].insert(l[i]);
		segl.modify(dl[i], {*cl[dl[i]].rbegin()});
		segr.modify(dr[i], {*cr[dr[i]].begin()});
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int t;
	std::cin >> t;

	while (t--) {
		solve();
	}

	return 0;
}

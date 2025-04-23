#include<bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f64 = long double;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

#ifndef ONLINE_JUDGE
#include "algo/debug.hpp"
#else
#define debug(...) (void)42
#endif

template<class T>
constexpr void chmax(T& x, T y) {
	if (y > x) {
		x = y;
	}
}

template<class T>
constexpr void chmin(T& x, T y) {
	if (y < x) {
		x = y;
	}
}

template<class Info>
struct SegmentTree {
	int n;
	std::vector<Info>info;

	SegmentTree() {}
	SegmentTree(int n) {
		this->n = n;
		info.assign(4 << std::__lg(n), Info());
	}

	void build(const auto& a) {
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

constexpr int inf = 2E9;
struct Info {
	int min = inf, max = 0;
};

Info operator+(const Info& a, const Info& b) {
	return {std::min(a.min, b.min), std::max(a.max, b.max)};
}

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, m, q;
	std::cin >> n >> m >> q;

	std::vector a(m + 1, std::vector<int>(n + 1));
	for (int i = 1; i <= n; i += 1) {
		for (int j = 1; j <= m; j += 1) {
			std::cin >> a[j][i];
		}
	}

	std::vector<SegmentTree<Info>>seg(m + 1);
	for (int j = 1; j <= m; j += 1) {
		seg[j] = SegmentTree<Info>(n);
		for (int i = 1; i <= n; i += 1) {
			a[j][i] |= a[j][i - 1];
			seg[j].modify(i, {a[j][i], a[j][i]});
		}
	}

	while (q--) {
		int m;
		std::cin >> m;
		std::map<int, std::array<int, 2>>rec;
		for (int i = 0; i < m; i += 1) {
			int r, c;
			char o;
			std::cin >> r >> o >> c;
			if (not rec.contains(r)) {
				rec[r] = {0, inf};
			}
			if (o == '<') {
				chmin(rec[r][1], c);
			} else {
				chmax(rec[r][0], c);
			}
		}
		int l = 1, r = n;
		for (const auto & [x, v] : rec) {
			const auto & [lo, hi] = v;
			int j = seg[x].findFirst(1, n, [&](const auto & u) {
				return u.max > lo;
			});
			if (j == -1) {
				l = n + 1;
			} else {
				chmax(l, j);
			}
			j = seg[x].findLast(1, n, [&](const auto & u) {
				return u.min < hi;
			});
			if (j == -1) {
				r = 0;
			} else {
				chmin(r, j);
			}
		}
		if (l <= r) {
			std::cout << l << '\n';
		} else {
			std::cout << -1 << '\n';
		}
	}
	return 0;
}
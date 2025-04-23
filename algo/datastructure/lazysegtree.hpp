template <class Info, class Tag>
requires requires(Info info, Tag tag) {info.apply(tag); tag.apply(tag);}
struct LazySegmentTree {
	int n;
	vector<Info>info;
	vector<Tag>tag;

	LazySegmentTree () = default;

	LazySegmentTree (const int & n) : n(n), info(4 << __lg(n)), tag(4 << __lg(n)) {}

	LazySegmentTree (const auto & a) : n(a.size() - 1), info(4 << __lg(n)), tag(4 << __lg(n)) {
		auto work = [&](auto && work, int p, int l, int r) {
			if (l == r) {
				info[p] = Info(a[l]);
				return ;
			}
			int mid = (l + r) >> 1;
			work(work, p << 1, l, mid);
			work(work, p << 1 | 1, mid + 1, r);
			info[p] = info[p << 1] + info[p << 1 | 1];
		};
		work(work, 1, 1, n);
	}

	void apply(int p, const Tag& t) {
		info[p].apply(t);
		tag[p].apply(t);
	}

	void pull(int p) {
		apply(p << 1, tag[p]);
		apply(p << 1 | 1, tag[p]);
		tag[p] = Tag();
	}

	void modify(int p, int l, int r, int x, const Info& v) {
		if (l == r) {
			info[p] = v;
			return ;
		}
		pull(p);
		int mid = (l + r) >> 1;
		if (x <= mid) {
			modify(p << 1, l, mid, x, v);
		} else {
			modify(p << 1 | 1, mid + 1, r, x, v);
		}
		info[p] = info[p << 1] + info[p << 1 | 1];
	}
	void modify(int p, const Info & v) {
		modify(1, 1, n, p, v);
	}

	Info range(int p, int l, int r, int L, int R) {
		if (l > R || r < L) {
			return Info();
		}
		if (L <= l && r <= R) {
			return info[p];
		}
		pull(p);
		int mid = (l + r) >> 1;
		return range(p << 1, l, mid, L, R) + range(p << 1 | 1, mid + 1, r, L, R);
	}

	Info range(int l, int r) {
		return range(1, 1, n, l, r);
	}

	Info operator()(int p) {
		return range(p, p);
	}

	Info operator()(int l, int r) {
		return range(l, r);
	}

	void apply(int p, int l, int r, int L, int R, const Tag& t) {
		if (l > R || r < L) {
			return ;
		}
		if (L <= l && r <= R) {
			apply(p, t);
			return ;
		}
		pull(p);
		int mid = (l + r) >> 1;
		apply(p << 1, l, mid, L, R, t);
		apply(p << 1 | 1, mid + 1, r, L, R, t);
		info[p] = info[p << 1] + info[p << 1 | 1];
	}

	void apply(int l, int r, const Tag& t) {
		apply(1, 1, n, l, r, t);
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
			return l;
		}
		pull(p);
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
			if (l != r) {
				pull(p);
			}
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
		pull(p);
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
			if (l != r) {
				pull(p);
			}
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
		pull(p);
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
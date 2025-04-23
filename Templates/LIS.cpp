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
	void build(std::vector<T> a) {
		auto work = [&](auto && self, int p, int l, int r) {
			if (l == r) {
				info[p] = Info(a[l], a[l]);
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
};

const int inf = INT_MAX;

struct Info {
	int val = 0;
};
Info operator+(const Info& a, const Info& b) {
	return {std::max(a.val, b.val)};
}

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, q;
	std::cin >> n >> q;

	std::vector<int>a(n + 1);
	for (int i = 1; i <= n; i += 1) {
		std::cin >> a[i];
	}

	std::vector<int>p(q + 1), x(q + 1), G(n + 1), F(q + 1);
	std::vector qry(n + 1, std::vector<std::pair<int, int>>());
	for (int i = 1; i <= q; i += 1) {
		std::cin >> p[i] >> x[i];
		qry[p[i]].push_back({i, x[i]});
	}


	std::vector<int>b{0};
	for (int i = 1; i <= n; i += 1) {
		b.push_back(a[i]);
	}
	for (int i = 1; i <= q; i += 1) {
		b.push_back(x[i]);
	}

	std::sort(b.begin() + 1, b.end());
	b.erase(std::unique(b.begin() + 1, b.end()), b.end());

	auto Find = [&](int y) {
		return std::lower_bound(b.begin() + 1, b.end(), y) - b.begin();
	};

	const int N = b.size();

	for (int i = 1; i <= n; i += 1) {
		G[i] = Find(a[i]);
	}
	for (int i = 1; i <= q; i += 1) {
		F[i] = Find(x[i]);
	}

	auto seg = SegmentTree<Info>(N);
	std::vector<int>fst(n + 1);
	for (int i = 1; i <= n; i += 1) {
		int pos = G[i];
		fst[i] = std::max(fst[i], seg.rangeQuery(1, pos - 1).val) + 1;
		auto y = seg.rangeQuery(pos, pos).val;
		seg.modify(pos, {std::max(fst[i], y)});
	}

	seg = SegmentTree<Info>(N);
	std::vector<int>nst(n + 1);
	for (int i = n; i >= 1; i -= 1) {
		int pos = G[i];
		nst[i] = std::max(nst[i], seg.rangeQuery(pos + 1, N).val) + 1;
		auto y = seg.rangeQuery(pos, pos).val;
		seg.modify(pos, {std::max(nst[i], y)});
	}

	int len = seg.rangeQuery(1, N).val;

	std::vector<int>f(q + 1), g(q + 1), ans(q + 1);

	seg = SegmentTree<Info>(N);

	for (int i = 1; i <= n; i += 1) {
		for (const auto & [x, y] : qry[i]) {
			int l = F[x];
			f[x] = std::max(f[x], seg.rangeQuery(1, l - 1).val) + 1;
		}
		int pos = G[i];
		seg.modify(pos, {std::max(seg.rangeQuery(pos, pos).val, fst[i])});
	}

	seg = SegmentTree<Info>(N);
	for (int i = n; i >= 1; i -= 1) {
		for (const auto & [x, y] : qry[i]) {
			int r = F[x];
			g[x] = std::max(g[x], seg.rangeQuery(r + 1, N).val) + 1;
		}
		int pos = G[i];
		seg.modify(pos, {std::max(seg.rangeQuery(pos, pos).val, nst[i])});
	}

	std::map<int, int>mp;
	for (int i = 1; i <= n; i += 1) {
		if (fst[i] + nst[i] - 1 == len) {
			mp[fst[i]] += 1;
		}
	}

	for (int i = 1; i <= q; i += 1) {
		if (f[i] + g[i] - 1 > len) {
			ans[i] = len + 1;
		} else if (fst[p[i]] + nst[p[i]] - 1 == len and mp[fst[p[i]]] == 1 and f[i] + g[i] - 1 < len) {
			ans[i] = len - 1;
		} else {
			ans[i] = len;
		}
	}

	for (int i = 1; i <= q; i += 1) {
		std::cout << ans[i] << "\n";
	}

	return 0;
}
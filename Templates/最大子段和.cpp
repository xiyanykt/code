#include<bits/stdc++.h>

using i64 = long long;

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
};

constexpr i64 inf = 1E18;

struct Info {
	i64 sum;
	i64 max = -inf, maxl = -inf, maxr = -inf;
};

Info operator+(const Info& a, const Info& b) {
	Info c {};
	c.sum = a.sum + b.sum;
	c.maxl = std::max(a.maxl, a.sum + b.maxl);
	c.maxr = std::max(b.maxr, a.maxr + b.sum);
	c.max = std::max({a.max, b.max, a.maxr + b.maxl});
	return c;
}

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	auto solve = [&]() {
		int n, k, x;
		std::cin >> n >> k >> x;

		std::vector<int>a(n + 1);
		for (int i = 1; i <= n; i += 1) {
			std::cin >> a[i];
		}

		if (x < 0) {
			k = n - k;
			x = -x;
		}

		SegmentTree<Info>s(n);
		for (int i = 1; i <= n; i += 1) {
			if (i <= k) {
				s.modify(i, {a[i] + x, a[i] + x, a[i] + x, a[i] + x});
			} else {
				s.modify(i, {a[i] - x, a[i] - x, a[i] - x, a[i] - x});
			}
		}

		i64 ans = s.info[1].max;
		for (int i = k + 1; i <= n; i += 1) {
			s.modify(i, {a[i] + x, a[i] + x, a[i] + x, a[i] + x});
			s.modify(i - k, {a[i - k] - x, a[i - k] - x, a[i - k] - x, a[i - k] - x});
			ans = std::max(ans, s.info[1].max);
		}
		std::cout << (std::max(0LL, ans)) << "\n";
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
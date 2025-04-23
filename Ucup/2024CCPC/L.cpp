#include<bits/stdc++.h>

using i64 = long long;

template <class Info>
struct SegmentTree {
	int n;
	std::vector<Info>info;

	SegmentTree() {}
	SegmentTree(int n) {
		this->n = n;
		info.assign(4 << std::__lg(n), Info());
	}

	void modify(int p, int l, int r, int L, int R, const Info& v) {
		if (l > R or r < L) {
			return;
		}
		if (L <= l and r <= R) {
			info[p] = v;
			return;
		}
		int mid = (l + r) / 2;
		modify(p << 1, l, mid, L, R, v);
		modify(p << 1 | 1, mid + 1, r, L, R, v);
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
		int mid = (l + r) / 2;
		return rangeQuery(p << 1, l, mid, L, R) + rangeQuery(p << 1 | 1, mid + 1, r, L, R);
	}
	Info rangeQuery(int l, int r) {
		return rangeQuery(1, 1, n, l, r);
	}

	template<class F>
	int findFirst(int p, int l, int r, int L, int R, const F& pred) {
		if (l > R or r < L or not pred(info[p])) {
			return -1;
		}
		if (l == r) {
			return l;
		}
		int mid = (l + r) / 2;
		int res = findFirst(p << 1, l, mid, L, R, pred);
		return res == -1 ? findFirst(p << 1 | 1, mid + 1, r, L, R, pred) : res;
	}
	template<class F>
	int findFirst(int l, int r, const F& pred) {
		return findFirst(1, 1, n, l, r, pred);
	}
};

template <class T>
struct Fenwick {
	int n;
	std::vector<T>a;

	Fenwick() {}
	Fenwick(int n) {
		this->n = n;
		a.resize(n + 1);
	}

	void add(int p, const T& x) {
		for (int i = p; i <= n; i += i & -i) {
			a[i] += x;
		}
	}

	T sum(int p) {
		T res = T{0};
		for (int i = p; i >= 1; i -= i & -i) {
			res += a[i];
		}
		return res;
	}

	T getRange(int l, int r) {
		return sum(r) - sum(l - 1);
	}
};

void solve() {
	int n, m;
	std::cin >> n >> m;

	std::vector<std::string>s(n);
	for (int i = 0; i < n; i += 1) {
		std::cin >> s[i];
	}

	int cnt = 0;

	for (int i = 0; i < n - 1; i += 1) {
		for (int j = 0; j < m - 1; j += 1) {
			if (s[i][j] == 'c' and s[i][j + 1] == 'c' and s[i + 1][j] == 'p' and s[i + 1][j + 1] == 'c') {
				cnt += 1;
			}
		}
	}

	std::cout << cnt << '\n';
}

auto main()->int32_t{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int t = 1;
	// std::cin >> t;

	while (t--) {
		solve();
	}

	return 0;
}
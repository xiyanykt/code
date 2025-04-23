#include<bits/stdc++.h>

using i64 = int64_t;

template<typename T>
struct Fenwick {
	int n;
	std::vector<T>a;

	Fenwick(const int n = 0): n(n), a(n + 1, T()) {}

	void add(int p, const T& v) {
		while (p <= n) {
			a[p] += v;
			p += p & -p;
		}
	}

	T sum(int p) {
		T res = T();
		while (p > 0) {
			res += a[p];
			p -= p & -p;
		}
		return res;
	}

	T getRange(int l, int r) {
		return sum(r) - sum(l - 1);
	}
};

template<class Info>
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
		int mid = l + r >> 1;
		modify(p << 1, l, mid, L, R, v), modify(p << 1 | 1, mid + 1, r, L, R, v);
		info[p] = info[p << 1] + info[p << 1 | 1];
	}
	void modify(int p, const Info & v) {
		modify(1, 1, n, p, p, v);
	}

	Info rangeQuery(int p, int l, int r, int L, int R) {
		if (l > R or r < L) {
			return Info();
		}
		if (L <= l and r <= R) {
			return info[p];
		}
		int mid = l + r >> 1;
		return rangeQuery(p << 1, l, mid, L, R) + rangeQuery(p << 1 | 1, mid + 1, r, L, R);
	}
	Info rangeQuery(int l, int r) {
		return rangeQuery(1, 1, n, l, r);
	}

	template<class F>
	int findLast(int p, int l, int r, int L, int R, const F& pred) {
		if (l > R or r < L or not pred(info[p])) {
			return -1;
		}
		if (l == r) {
			return r;
		}
		int mid = l + r >> 1;
		int res = findLast(p << 1 | 1, mid + 1, r, L, R, pred);
		return res == -1 ? findLast(p << 1, l, mid, L, R, pred) : res;
	}

	template<class F>
	int findLast(int l, int r, const F& pred) {
		return findLast(1, 1, n, l, r, pred);
	}
};

struct Info {
	int val = 0;
};
Info operator+(const Info &a, const Info &b) {
	return {std::max(a.val, b.val)};
}

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	auto solve = [&]() {
		int n;
		std::cin >> n;

		std::vector<int>a(n + 1);
		for (int i = 1; i <= n; i += 1) {
			std::cin >> a[i];
		}

		int N = *std::ranges::max_element(a);

		SegmentTree<Info>seg(N);
		for (int i = 1; i <= n; i += 1) {
			seg.modify(a[i], {1});
		}

		std::set<int>S;
		for (int i = 1; i <= n; i += 1) {
			S.insert(-a[i]);
		}

		int ans = 0;
		for (const auto & u : S) {
			int v = -u;
			if (ans >= v) {
				break;
			}
			for (int j = v; j <= N; j += v) {
				auto y = seg.findLast(j, j + v - 1, [&](const auto & u) {
					return u.val > 0;
				});
				if (y != -1) {
					ans = std::max(ans, y - j);
				}
			}
		}
		std::cout << ans << "\n";
	};

	int t = 1;
	//std::cin>>t;
	while (t--) {
		solve();
	}

	return 0;
}

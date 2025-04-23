#include<bits/stdc++.h>

using i64 = int64_t;

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int rand(int l, int r) {
	return std::uniform_int_distribution<int>(l, r)(rng);
}

bool isPri(int n) {
	if (n <= 1)return false;
	for (int i = 2; i * i <= n; ++i) {
		if (n % i == 0)return false;
	}
	return true;
}

int gene(int l, int r) {
	int x = rand(l, r);
	while (!isPri(x)) {
		x += 1;
	}
	return x;
}

// const int MOD1 = gene(1e7, 1e8);
// const int MOD2 = gene(1e8, 1e9);
const int MOD1 = 1e9 + 7;
// const int MOD2 = 998244353;
const int MOD2 = 233333333;
const int BASE1 = 17 + rand(0, 13);
const int BASE2 = 37 + rand(0, 13);

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

	template<class F>
	int findFirst(int p, int l, int r, int L, int R, F pred) {
		if (l > R or r < L or not pred(info[p])) {
			return -1;
		}
		if (l == r) {
			return l;
		}
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
			return r;
		}
		int mid = std::midpoint(l, r);
		int res = findLast(p << 1 | 1, mid + 1, r, L, R, pred);
		return res == -1 ? findLast(p << 1, l, mid, L, R, pred) : res;
	}
	template<class F>
	int findLast(int l, int r, F pred) {
		return findLast(1, 1, n, l, r, pred);
	}
};

constexpr int inf = 1E9;

constexpr int M = 1E6;

int pre1[M + 1], pre2[M + 1];

struct Info {
	int len = 0;
	int x = 0;
	int y = 0;
};
Info operator+(const Info& a, const Info& b) {
	if (a.len == 0) {
		return b;
	}
	if (b.len == 0) {
		return a;
	}
	Info c {};
	c.len = a.len + b.len;
	c.x = (1LL * a.x * pre1[b.len] % MOD1 + b.x) % MOD1;
	c.y = (1LL * a.y * pre2[b.len] % MOD2 + b.y) % MOD2;
	return c;
}

#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) (void)42
#endif

std::pair<int, int> Hash(const std::string &s) {
	int n = s.size();
	int x = 0;
	int y = 0;
	for (int i = 1; i <= n; i += 1) {
		x = (1LL * x * BASE1 % MOD1 + s[i - 1]) % MOD1;
		y = (1LL * y * BASE2 % MOD2 + s[i - 1]) % MOD2;
	}
	return {x, y};
}

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	pre1[0] = pre2[0] = 1;
	for (int i = 1; i <= M; i += 1) {
		pre1[i] = 1LL * pre1[i - 1] * BASE1 % MOD1;
		pre2[i] = 1LL * pre2[i - 1] * BASE2 % MOD2;
	}

	int n, q;
	std::cin >> n >> q;

	std::set<std::pair<int, int>>S;
	for (int i = 1; i <= n; i += 1) {
		std::string s;
		std::cin >> s;
		S.insert(Hash(s));
	}

	auto work = [&]() {
		std::string s;
		std::cin >> s;

		int m = s.size();
		SegmentTree<Info>seg(m);
		for (int i = 1; i <= m; i += 1) {
			seg.modify(i, {1, s[i - 1], s[i - 1]});
		}

		for (int i = 1; i <= m; i += 1) {
			auto bef = s[i - 1];
			for (char x = 'a'; x <= 'c'; x += 1) {
				if (x == bef) {
					continue;
				}
				seg.modify(i, {1, x, x});
				auto y = seg.rangeQuery(1, m);
				if (S.contains(std::make_pair(y.x, y.y))) {
					std::cout << "YES\n";
					return;
				}
			}
			seg.modify(i, {1, bef, bef});
		}
		std::cout << "NO\n";
	};

	while (q--) {
		work();
	}

	return 0;
}

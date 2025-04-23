#include<bits/stdc++.h>

using i64 = int64_t;
using u64 = unsigned long long;

template<class Info, class Tag>
struct LazySegmengtree {
	int n;
	std::vector<Info>info;
	std::vector<Tag>tag;

	LazySegmengtree () {}
	LazySegmengtree (int n) {
		this->n = n;
		info.assign(4 << std::__lg(n), Info()), tag.assign(4 << std::__lg(n), Tag());
	}

	template<typename T>
	void build(std::vector<T> a) {
		auto work = [&](auto && self, int p, int l, int r) {
			if (l == r) {
				info[p] = Info(a[l]);
				return;
			}
			// int mid = std::midpoint(l, r);
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
		// int mid = std::midpoint(l, r);
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
		// int mid = std::midpoint(l, r);
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
		// int mid = std::midpoint(l, r);
		int mid = l + r >> 1;
		rangeApply(p << 1, l, mid, L, R, v), rangeApply(p << 1 | 1, mid + 1, r, L, R, v);
		info[p] = info[p << 1] + info[p << 1 | 1];
	}
	void rangeApply(int l, int r, const Tag& v) {
		rangeApply(1, 1, n, l, r, v);
	}

	// template<class F>
	// int findFirst(int p, int l, int r, int L, int R, F pred) {
	// 	if (l > R or r < L or not pred(info[p])) {
	// 		return -1;
	// 	}
	// 	if (l == r) {
	// 		return l;
	// 	}
	// 	pull(p);
	// 	int mid = std::midpoint(l, r);
	// 	int res = findFirst(p << 1, l, mid, L, R, pred);
	// 	return res == -1 ? findFirst(p << 1 | 1, mid + 1, r, L, R, pred) : res;
	// }
	// template<class F>
	// int findFirst(int l, int r, F pred) {
	// 	return findFirst(1, 1, n, l, r, pred);
	// }

	// template<class F>
	// int findLast(int p, int l, int r, int L, int R, F pred) {
	// 	if (l > R or r < L or not pred(info[p])) {
	// 		return -1;
	// 	}
	// 	if (l == r) {
	// 		return l;
	// 	}
	// 	pull(p);
	// 	int mid = std::midpoint(l, r);
	// 	int res = findLast(p << 1 | 1, mid + 1, r, L, R, pred);
	// 	return res == -1 ? findLast(p << 1, l, mid, L, R, pred) : res;
	// }
	// template<class F>
	// int findLast(int l, int r, F pred) {
	// 	return findLast(1, 1, n, l, r, pred);
	// }
};

constexpr i64 inf = 1E18;

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

const int MOD = 998244353;
// const int MOD = 1e9 + 7;
const int BASE = 37;
// const u64 BASE = 37;

const int N = 2e5;
// u64 Pow[N + 1], sPow[N + 1];
int Pow[N + 1], sPow[N + 1];

struct Tag {
	int add = -1;
	void apply(const Tag& t) {
		if (t.add == -1) {
			return;
		}
		add = t.add;
	}
};
struct Info {
	int len = 0;
	int pre = -1, suf = -1;
	void apply(const Tag& t) {
		if (t.add == -1) {
			return;
		}
		int v = 1LL * t.add * sPow[len - 1] % MOD;
		pre = suf = v;
	}
};
Info operator+(const Info& a, const Info& b) {
	Info c {};
	c.len = a.len + b.len;
	if (a.pre == -1) {
		return b;
	}
	if (b.suf == -1) {
		return a;
	}
	c.pre = (1LL * a.pre * Pow[b.len] % MOD + b.pre) % MOD;
	c.suf = (1LL * b.suf * Pow[a.len] % MOD + a.suf) % MOD;
	return c;
}

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	sPow[0] = Pow[0] = 1;
	for (int i = 1; i <= N; i += 1) {
		Pow[i] = 1LL * Pow[i - 1] * BASE % MOD;
		sPow[i] = (1LL * sPow[i - 1] + Pow[i]) % MOD;
	}

	int n, q;
	std::cin >> n >> q;

	std::string s;
	std::cin >> s;

	LazySegmengtree<Info, Tag>seg(n);
	for (int i = 1; i <= n; i += 1) {
		seg.modify(i, {1, s[i - 1] ^ 7, s[i - 1] ^ 7});
	}

	while (q--) {
		int op, l, r;
		std::cin >> op >> l >> r;

		if (op == 1) {
			auto p = seg.rangeQuery(l, r);
			if (p.pre == p.suf) {
				std::cout << "YES\n";
				continue;
			}

			int lo = l, hi = (l + r) / 2;
			while (lo <= hi) {
				int mid = lo + hi >> 1;
				auto x = seg.rangeQuery(l, mid), y = seg.rangeQuery(r - mid + l, r);
				if (x.pre == y.suf) {
					lo = mid + 1;
				} else {
					hi = mid - 1;
				}
			}

			int x = hi + 1, y = r - hi - 1 + l;
			if (x + 1 == y) {
				std::cout << "YES\n";
			} else {
				auto v = seg.rangeQuery(x + 1, y - 1);
				std::cout << (v.pre == v.suf ? "YES\n" : "NO\n");
			}
		} else {
			char c;
			std::cin >> c;
			seg.rangeApply(l, r, {c ^ 7});
		}
	}
	return 0;
}
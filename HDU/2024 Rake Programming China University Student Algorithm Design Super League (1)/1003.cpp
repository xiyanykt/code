#include<bits/stdc++.h>

using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128_t;
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

constexpr int inf = 1E6;
struct Node {
	Node *lsh = nullptr, *rsh = nullptr;
	int cnt = 0;
	u64 sum = 0;
	u64 prd = 0;
};

Node operator+(const Node& a, const Node& b) {
	return {nullptr, nullptr, a.cnt + b.cnt, a.sum + b.sum, a.prd + b.prd};
}

void add(Node*& t, int l, int r, int x) {
	if (t == nullptr) {
		t = new Node();
	}
	t->cnt += 1;
	t->sum += x;
	t->prd += 1ull * x * x;
	if (l == r) {
		return ;
	}
	int mid = (l + r) >> 1;
	if (x <= mid) {
		add(t->lsh, l, mid, x);
	} else {
		add(t->rsh, mid + 1, r, x);
	}
}

Node* merge(Node* a, Node* b, int l, int r) {
	if (a == nullptr) {
		return b;
	}
	if (b == nullptr) {
		return a;
	}
	a->cnt += b->cnt;
	a->sum += b->sum;
	a->prd += b->prd;
	if (l == r) {
		return a;
	}
	int mid = (l + r) >> 1;
	a->lsh = merge(a->lsh, b->lsh, l, mid);
	a->rsh = merge(a->rsh, b->rsh, mid + 1, r);
	return a;
}

Node query(Node* t, int l, int r, int L, int R) {
	if (l > R or r < L or t == nullptr) {
		return Node();
	}
	if (L <= l and r <= R) {
		return Node(nullptr, nullptr, t->cnt, t->sum, t->prd);
	}
	int mid = (l + r) >> 1;
	return query(t->lsh, l, mid, L, R) + query(t->rsh, mid + 1, r, L, R);
}

template<typename T>
struct Fenwick {
	int n;
	std::vector<T>a;

	Fenwick() {}
	Fenwick(int n) {
		this->n = n;
		a.assign(n + 1, T());
	}

	void add(int p, const T& x) {
		for (int i = p; i <= n; i += i & -i) {
			a[i] += x;
		}
	}

	T sum(int p) {
		T ans = T();
		for (int i = p; i > 0; i -= i & -i) {
			ans += a[i];
		}
		return ans;
	}

	T getRange(int l, int r) {
		return sum(r) - sum(l - 1);
	}

	int select(int k) {
		int x = 0;
		T cur = T();
		for (int i = std::__lg(n); ~i; i -= 1) {
			x += 1 << i;
			if (x >= n or cur + a[x] >= k) {
				x -= 1 << i;
			} else {
				cur = cur + a[x];
			}
		}
		return x + 1;
	}
};

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout << std::fixed << std::setprecision(13);

	int n;
	std::cin >> n;
	std::vector<std::vector<int>>adj(n + 1);
	for (int i = 1; i <= n - 1; i += 1) {
		int u, v;
		std::cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	std::vector<u64>a(n + 1);
	for (int i = 1; i <= n; i += 1) {
		std::cin >> a[i];
	}

	int low = 1;
	std::vector<int>son(n + 1), siz(n + 1), par(n + 1), dfn(n + 1), seq(n + 1);
	auto dfs = [&](auto && self, int u) ->void {
		siz[u] += 1;
		dfn[u] = low;
		seq[low] = u;
		low += 1;
		for (const auto& v : adj[u]) {
			if (v == par[u]) {
				continue;
			}
			par[v] = u;
			self(self, v);
			siz[u] += siz[v];
			if (siz[son[u]] < siz[v]) {
				son[u] = v;
			}
		}
	};
	dfs(dfs, 1);

	u64 ans = 0, cur = 0;
	constexpr int N = 1E6;
	Fenwick<int>cnt(N);
	Fenwick<u64>s(N), p(N);
	auto add = [&](int i) {
		cur += 1ull * a[i] * a[i] * cnt.sum(a[i] - 1) - 1ull * a[i] * s.sum(a[i] - 1);
		cur += 1ull * p.getRange(a[i] + 1, N) - 1ull * a[i] * s.getRange(a[i] + 1, N);
		p.add(a[i], 1ull * a[i] * a[i]);
		s.add(a[i], a[i]);
		cnt.add(a[i], 1);
	};

	auto del = [&](int i) {
		cur -= 1ull * a[i] * a[i] * cnt.sum(a[i] - 1) - 1ull * a[i] * s.sum(a[i] - 1);
		cur -= 1ull * p.getRange(a[i] + 1, N) - 1ull * a[i] * s.getRange(a[i] + 1, N);
		p.add(a[i], -1ull * a[i] * a[i]);
		s.add(a[i], -a[i]);
		cnt.add(a[i], -1);
	};

	std::vector<u64>f(n + 1);
	auto work = [&](auto && work, int u, int top = 0) ->void {
		for (const auto & v : adj[u]) {
			if (v == par[u] or v == son[u]) {
				continue;
			}
			work(work, v);
		}
		if (son[u]) {
			work(work, son[u], 1);
		}
		for (const auto & v : adj[u]) {
			if (v == par[u] or v == son[u]) {
				continue;
			}
			for (int j = dfn[v]; j <= dfn[v] + siz[v] - 1; j += 1) {
				add(seq[j]);
			}
		}
		add(u);
		f[u] = cur;
		if (not top) {
			for (int j = dfn[u]; j <= dfn[u] + siz[u] - 1; j += 1) {
				del(seq[j]);
			}
		}
	};
	work(work, 1);

	for (int i = 1; i <= n; i += 1) {
		ans ^= 2ull * f[i];
	}
	std::cout << ans << '\n';
	return 0;
}
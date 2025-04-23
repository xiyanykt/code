#include<bits/stdc++.h>

using i64 = long long;

struct Discretization {
	int n;

	struct Point {
		int val, id;
	};

	std::vector<Point>y;
	std::vector<int>p;

	Discretization() {}

	Discretization(int n) {
		this->n = n;
		y.resize(n + 1), p.resize(n + 1);
	}

	void build(const std::vector<int>& a) {
		for (int i = 1; i <= n; i += 1) {
			y[i].val = a[i], y[i].id = i;
		}
		std::sort(y.begin() + 1, y.end(), [&](const Point & i, const Point & j) {
			return i.val == j.val ? i.id < j.id : i.val < j.val;
		});
		for (int j = 1; j <= n; j += 1) {
			p[y[j].id] = j;
		}
	}

	void unique(const std::vector<int>& a) {
		auto b = a;
		std::sort(b.begin() + 1, b.end());
		b.erase(std::unique(b.begin() + 1, b.end()), b.end());
		for (int i = 1; i <= n; i += 1) {
			p[i] = std::lower_bound(b.begin() + 1, b.end(), a[i]) - b.begin();
		}
	}

	inline int get(int x) {
		return p[x];
	}
};

const int N = 2e5 + 1;
int ls[N << 5], rs[N << 5], rt[N << 5], cnt[N << 5], tot = 0;

std::vector<int>a;

void build(int& o, int l, int r) {
	o = ++tot;
	if (l == r) {
		return;
	}
	int mid = std::midpoint(l, r);
	build(ls[o], l, mid), build(rs[o], mid + 1, r);
}

void update(int lst, int& o, int l, int r, int x) {
	o = ++tot;
	ls[o] = ls[lst], rs[o] = rs[lst], cnt[o] = cnt[lst] + 1;
	if (l == r) {
		return;
	}
	int mid = std::midpoint(l, r);
	if (x <= mid) {
		update(ls[lst], ls[o], l, mid, x);
	} else {
		update(rs[lst], rs[o], mid + 1, r, x);
	}
}

int query(int u, int v, int l, int r, int k) {
	int mid = std::midpoint(l, r), x = cnt[ls[v]] - cnt[ls[u]];
	if (l == r) {
		return l;
	}
	if (k <= x) {
		return query(ls[u], ls[v], l, mid, k);
	} else {
		return query(rs[u], rs[v], mid + 1, r, k - x);
	}
}
int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, q; std::cin >> n >> q;
	a.resize(n + 1);
	for (int i = 1; i <= n; i += 1) {
		std::cin >> a[i];
	}

	Discretization L(n);
	L.build(a);

	build(rt[0], 0, n);
	for (int j = 1; j <= n; j += 1) {
		update(rt[j - 1], rt[j], 0, n, L.get(j));
	}
	while (q--) {
		int l, r, k; std::cin >> l >> r >> k;
		std::cout << L.y[query(rt[l - 1], rt[r], 0, n, k)].val << "\n";
	}
	return 0;
}
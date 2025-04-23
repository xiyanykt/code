#include<bits/stdc++.h>

using i64 = long long;

const int N = 1e6 + 1;
int ls[N << 5], rs[N << 5], val[N << 5], rt[N << 5], tot = 0, a[N];

void build(int& o, int l, int r) {
	o = ++tot;
	if (l == r) {
		val[o] = a[l];
		return;
	}
	int mid = std::midpoint(l, r);
	build(ls[o], l, mid), build(rs[o], mid + 1, r);
}
void update(int lst, int& o, int l, int r, int q, int v) {
	o = ++tot;
	ls[o] = ls[lst], rs[o] = rs[lst], val[o] = val[lst];
	if (l == r) {
		val[o] = v;
		return;
	}
	int mid = std::midpoint(l, r);
	if (q <= mid) {
		update(ls[lst], ls[o], l, mid, q, v);
	} else {
		update(rs[lst], rs[o], mid + 1, r, q, v);
	}
}
int query(int o, int l, int r, int q) {
	if (l == r) {
		return val[o];
	}
	int mid = std::midpoint(l, r);
	if (q <= mid) {
		return query(ls[o], l, mid, q);
	} else {
		return query(rs[o], mid + 1, r, q);
	}
}
int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, m; std::cin >> n >> m;
	for (int i = 1; i <= n; i += 1) {
		std::cin >> a[i];
	}

	build(rt[0], 1, n);
	for (int i = 1; i <= m; i += 1) {
		int lst, op; std::cin >> lst >> op;
		if (op == 1) {
			int p, v; std::cin >> p >> v;
			update(rt[lst], rt[i], 1, n, p, v);
		} else {
			int p; std::cin >> p;
			auto z = query(rt[lst], 1, n, p);
			rt[i] = rt[lst];
			std::cout << z << "\n";
		}
	}

	return 0;
}
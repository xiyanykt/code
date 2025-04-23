#include<bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1e9 + 13;

struct Info {
	int max = -inf, min = inf;
};
Info operator+(const Info& a, const Info& b) {
	return {std::max(a.max, b.max), std::min(a.min, b.min)};
}

struct Tag {
	int v = -1;
};

const int N = 2e5 + 1;
Info info[N << 2];
Tag tag[N << 2];

void pull(int p) {
	if (tag[p].v == -1)return;
	tag[p << 1].v = tag[p << 1 | 1].v = tag[p].v;
	info[p << 1].max = info[p << 1].min = info[p << 1 | 1].max = info[p << 1 | 1].min = tag[p].v;
	tag[p].v = 0;
}

void modify(int p, int l, int r, int L, int R, const Info& x) {
	if (l > R or r < L) {
		return;
	}
	if (L <= l and r <= R) {
		info[p] = x, tag[p].v = x.max;
		return;
	}
	pull(p);
	int mid = std::midpoint(l, r);
	modify(p << 1, l, mid, L, R, x), modify(p << 1 | 1, mid + 1, r, L, R, x);
	info[p] = info[p << 1] + info[p << 1 | 1];
}

Info query(int p, int l, int r, int L, int R) {
	if (l > R or r < L) {
		return Info();
	}
	if (L <= l and  r <= R) {
		return info[p];
	}
	pull(p);
	int mid = std::midpoint(l, r);
	return query(p << 1, l, mid, L, R) + query(p << 1 | 1, mid + 1, r, L, R);
}
#include<bits/stdc++.h>

using i64 = long long;

template<typename T>
struct Discretization {
	int n;

	struct Point {
		T val;
		int id;
	};

	std::vector<Point>y;
	std::vector<int>p;

	Discretization() {}

	Discretization(int n) {
		this->n = n;
		y.resize(n + 1), p.resize(n + 1);
	}

	void build(const std::vector<T>& a) {
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

	void unique(const std::vector<T>& a) {
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
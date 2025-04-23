#include<bits/stdc++.h>

#pragma GCC optimize("O2")
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
#pragma GCC target("sse4,popcnt,abm,mmx")

using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;

#ifndef ONLINE_JUDGE
#include "algo\debug.hpp"
#else
#define debug(...) (void)42
#endif

template<class T>
void chmax(T& x, T y) {
	x = std::max(x, y);
}

template<class T>
void chmin(T& x, T y) {
	x = std::min(x, y);
}

template<class T>
struct Point {
	T x;
	T y;
	Point(const T& x = 0, const T& y = 0): x(x), y(y) {}

	Point& operator+=(const Point& p)& {
		x += p.x;
		y += p.y;
		return *this;
	}

	Point& operator*=(const Point& p)& {
		x *= p.x;
		y *= p.y;
		return *this;
	}

	Point& operator-=(const Point& p)& {
		x -= p.x;
		y -= p.y;
		return *this;
	}

	Point& operator/=(const Point& p)& {
		x /= p.x;
		y /= p.y;
		return *this;
	}

	constexpr friend Point operator+(Point a, const Point& b) {
		return a += b;
	}
	constexpr friend Point operator-(Point a, const Point& b) {
		return a -= b;
	}
	constexpr friend Point operator*(Point a, const Point& b) {
		return a *= b;
	}
	constexpr friend Point operator/(Point a, const Point& b) {
		return a /= b;
	}
	constexpr friend bool operator==(const Point& a, const Point& b) {
		return (a.x == b.x and a.y == b.y);
	}
	constexpr friend std::istream& operator>>(std::istream& is, Point& p) {
		return is >> p.x >> p.y;
	}
	constexpr friend std::ostream& operator<<(std::ostream& os, Point& p) {
		return os << '{' << p.x << ' ' << p.y << '}';
	}
};

using P = Point<i64>;

i64 dot(const P& a, const P& b) {
	return a.x * b.x + a.y * b.y;
}

i64 cross(const P& a, const P& b) {
	return a.x * b.y - a.y * b.x;
}

i64 square(const P& a) {
	return dot(a, a);
}

f64 length(const P& a) {
	return sqrtl(square(a));
}

int sgn(const P& a) {
	return a.y > 0 || (a.y == 0 && a.x > 0) ? 1 : -1;
}

f64 computeAngle(const P& a) {
	return atan2(a.y, a.x);
}

std::vector<P> getHull(std::vector<P> p) {
	std::vector<P>h, l;
	std::sort(p.begin(), p.end(), [&](const P & a, const P & b) {
		return a.x == b.x ? a.y < b.y : a.x < b.x;
	});
	p.erase(std::unique(p.begin(), p.end()), p.end());
	if ((int)p.size() <= 1) {
		return p;
	}
	for (const auto & a : p) {
		while ((int)h.size() > 1 and cross(a - h.back(), a - h[(int)h.size() - 2]) <= 0) {
			h.pop_back();
		}
		while ((int)l.size() > 1 and cross(a - l.back(), a - l[(int)l.size() - 2]) >= 0) {
			l.pop_back();
		}
		l.push_back(a);
		h.push_back(a);
	}
	l.pop_back();
	std::reverse(h.begin(), h.end());
	h.pop_back();
	l.insert(l.end(), h.begin(), h.end());
	return l;
}

f64 convexDiameter(const std::vector<P>& p) {
	std::vector<P> ret = getHull(p);
	int n = ret.size();
	if (n <= 2) {
		return length(ret[0] - ret.back());
	}
	int j = 1;
	f64 ans = 0.0;
	for (int i = 0; i < n; i += 1) {
		while (length(ret[i] - ret[(j + 1) % n]) > length(ret[i] - ret[j])) {
			j = (j + 1) % n;
		}
		ans = std::max(ans, length(ret[i] - ret[j]));
	}
	return ans;
}

i64 convexLongest(const std::vector<P>& p) {
	if (p.size() <= 2) {
		return square(p[0] - p.back());
	}
	int n = p.size();
	i64 ans = 0;
	for (int i = 0, j = 2; i < n; i += 1) {
		while (std::abs(cross(p[(i + 1) % n] - p[i], p[j] - p[i])) <= std::abs(cross(p[(i + 1) % n] - p[i], p[(j + 1) % n] - p[i]))) {
			j = (j + 1) % n;
		}
		ans = std::max({ans, square(p[i] - p[j]), square(p[(i + 1) % n] - p[j])});
	}
	return ans;
}

struct Node {
	i64 y, l, r;
	int type;
	Node(const i64 y, const i64 l, const i64 r, const int type): y(y), l(l), r(r), type(type) {}
	constexpr friend bool operator<(const Node& a, const Node& b) {
		return a.y < b.y;
	}
};
template<class T = i64>
struct SegmentTree {
	int n;
	std::vector<T>info;
	std::vector<T>tag;
	std::vector<T>X;

	SegmentTree() {}
	SegmentTree(const auto & xs) {
		X = xs;
		n = (int)xs.size() - 2;
		info.assign(8 * n, T());
		tag.assign(8 * n, T());
	}

	void pull(int p, int l, int r) {
		if (tag[p] != 0) {
			info[p] = X[r + 1] - X[l];
		} else {
			info[p] = info[p << 1] + info[p << 1 | 1];
		}
	}

	void update(int p, int l, int r, int L, int R, const T& val) {
		if (X[r + 1] <= L or X[l] >= R) {
			return;
		}
		if (L <= X[l] and X[r + 1] <= R) {
			tag[p] += val;
			pull(p, l, r);
			return;
		}
		int mid = l + r >> 1;
		update(p << 1, l, mid, L, R, val);
		update(p << 1 | 1, mid + 1, r, L, R, val);
		pull(p, l, r);
	}
	void update(int l, int r, const T& val) {
		update(1, 1, n, l, r, val);
	}

	T Query() {
		return info[1];
	}
};

i64 convexArea(const std::vector<std::array<i64, 4>>& ret) {
	std::vector<Node>e;
	std::vector<i64>xs{0};
	for (const auto & [x1, y1, x2, y2] : ret) {
		e.push_back({y1, x1, x2, 1});
		e.push_back({y2, x1, x2, -1});
		xs.push_back(x1);
		xs.push_back(x2);
	}

	std::sort(e.begin(), e.end());
	std::sort(xs.begin() + 1, xs.end());
	xs.erase(std::unique(xs.begin() + 1, xs.end()), xs.end());

	SegmentTree seg(xs);
	i64 ans = 0;
	for (int i = 0; i + 1 < (int)e.size(); i += 1) {
		seg.update(e[i].l, e[i].r, e[i].type);
		ans += seg.Query() * (e[i + 1].y - e[i].y);
	}
	return ans;
}

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cout << std::fixed << std::setprecision(13);

	auto solve = [&]() {
		int n;
		std::cin >> n;

		std::vector<P>a(n);
		for (auto & c : a) {
			std::cin >> c;
		}

		int m;
		std::cin >> m;

		std::vector<P>b(m);
		for (auto & c : b) {
			std::cin >> c;
		}

		f64 ans = 0;
		for (int i = 0; i < n; i += 1) {
			ans += length(a[(i + 1) % n] - a[i]);
		}

		constexpr f64 pi = acos(-1);

		ans += 2.L * pi * sqrtl(convexLongest(b));
		std::cout << ans << "\n";
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
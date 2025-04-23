#include<bits/stdc++.h>

using i64 = int64_t;

template<class T>
struct Point {
	T x;
	T y;
	Point(const T & _x = 0, const T& _y = 0): x(_x), y(_y) {}

	template<class U>
	operator Point<U>() {
		return Point<U>(U(x), U(y));
	}

	Point &operator+=(const Point &p) & {
		x += p.x;
		y += p.y;
		return *this;
	}
	Point &operator-=(const Point &p) & {
		x -= p.x;
		y -= p.y;
		return *this;
	}
	Point &operator*=(const T &v) & {
		x *= v;
		y *= v;
		return *this;
	}
	Point &operator/=(const T &v) & {
		x /= v;
		y /= v;
		return *this;
	}
	Point operator-() const {
		return Point(-x, -y);
	}
	friend Point operator+(Point a, const Point &b) {
		return a += b;
	}
	friend Point operator-(Point a, const Point &b) {
		return a -= b;
	}
	friend Point operator*(Point a, const T &b) {
		return a *= b;
	}
	friend Point operator/(Point a, const T &b) {
		return a /= b;
	}
	friend Point operator*(const T &a, Point b) {
		return b *= a;
	}
	friend bool operator==(const Point &a, const Point &b) {
		return a.x == b.x && a.y == b.y;
	}
	friend std::istream &operator>>(std::istream &is, Point &p) {
		return is >> p.x >> p.y;
	}
	friend std::ostream &operator<<(std::ostream &os, const Point &p) {
		return os << "{" << p.x << ", " << p.y << "}";
	}
};

template<class T>
T dot(const Point<T>& a, const Point<T>& b) {
	return a.x * b.x + a.y * b.y;
}

template<class T>
T cross(const Point<T>& a, const Point<T>& b) {
	return a.x * b.y - a.y * b.x;
}

template<class T>
T square(const Point<T>& a) {
	return (dot(a, a));
}

template<class T>
double length(const Point<T>& p) {
	return std::sqrt(square(p));
}

template<class T>
int sgn(const Point<T> &a) {
	return a.y > 0 || (a.y == 0 && a.x > 0) ? 1 : -1;
}

template<class T>
std::vector<Point<T>> getHull(std::vector<Point<T>>p) {
	std::vector<Point<T>>h, l;

	std::sort(p.begin(), p.end(), [&](const auto & a, const auto & b) {
		return a.x == b.x ? a.y < b.y : a.x < b.x;
	});

	p.erase(std::unique(p.begin(), p.end()), p.end());
	if (p.size() <= 1) {
		return p;
	}

	for (const auto & a : p) {
		while (h.size() > 1 and cross(a - h.back(), a - h[h.size() - 2]) <= 0) {
			h.pop_back();
		}
		while (l.size() > 1 and cross(a - l.back(), a - l[l.size() - 2]) >= 0) {
			l.pop_back();
		}
		l.push_back(a);
		h.push_back(a);
	}

	l.pop_back();
	std::ranges::reverse(h);
	h.pop_back();
	l.insert(l.end(), h.begin(), h.end());
	return l;
}

using P = Point<i64>;

#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) (void)42
#endif

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n;
	std::cin >> n;

	std::vector<P>p(n + 1);
	for (int i = 1; i <= n; i += 1) {
		std::cin >> p[i];
	}

	std::vector<int>l(n + 1);
	std::iota(l.begin(), l.end(), 0);
	std::sort(l.begin() + 1, l.end(), [&](const auto & i, const auto & j) {
		return p[i].x == p[j].x ? p[i].y < p[j].y : p[i].x < p[j].x;
	});

	for (int i = 3; i <= n; i += 1) {
		auto y = cross(p[l[i]] - p[l[i - 2]], p[l[i - 1]] - p[l[i - 2]]);
		if (y) {
			std::cout << l[i-2] << " " << l[i - 1] << " " << l[i] << "\n";
			return 0;
		}
	}

	return 0;
}
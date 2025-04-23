template<class T>
struct Point {
	T x;
	T y;
	Point(const T& x = 0, const T& y = 0): x(x), y(y) {}

	template<class Tp>
	operator Point<Tp>() {
		return Point<Tp>(Tp(x), Tp(y));
	}

	Point &operator+=(const Point& p)& {
		x += p.x;
		y += p.y;
		return *this;
	}
	Point &operator-=(const Point& p)& {
		x -= p.x;
		y -= p.y;
		return *this;
	}
	Point &operator*=(const T& v)& {
		x *= v;
		y *= v;
		return *this;
	}
	Point &operator/=(const T& v)& {
		x *= v;
		y *= v;
		return *this;
	}

	Point operator-() const {
		return Point(-x, -y);
	}
	constexpr friend Point operator+(Point a, const Point& b) {
		return a += b;
	}
	constexpr friend Point operator-(Point a, const Point& b) {
		return a -= b;
	}
	constexpr friend Point operator*(Point a, const T& v) {
		return a *= v;
	}
	constexpr friend Point operator/(Point a, const T& v) {
		return a /= v;
	}
	constexpr friend bool operator==(const Point& a, const Point& b) {
		return a.x == b.x and a.y == b.y;
	}
	constexpr friend bool operator<(const Point& a, const Point& b) {
		return (a.x == b.x ? a.y < b.y : a.x < b.x);
	}
	friend std::istream& operator>>(std::istream& is, Point& p) {
		return is >> p.x >> p.y;
	}
	friend std::ostream& operator<<(std::ostream& os, Point& p) {
		return os << '(' << p.x << ' ' << p.y << ')';
	}
};

template<class T>
struct Line {
	Point<T> a;
	Point<T> b;
	Line(const Point<T>& a = Point<T>(), const Point<T>& b = Point<T>()): a(a), b(b) {}
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

struct Node {
	i64 y, l, r;
	int type;
	Node(const i64 y, const i64 l, const i64 r, const int type): y(y), l(l), r(r), type(type) {}
	constexpr friend bool operator<(const Node& a, const Node& b) {
		return a.y < b.y;
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
	return dot(a, a);
}

template<class T>
f64 length(const Point<T>& a) {
	return sqrtl(square(a));
}

template<class T>
f64 length(const Line<T>& l) {
	return length(l.a - l.b);
}

template<class T>
Point<T> normlize(const Point<T>& p) {
	return p / length(p);
}

template<class T>
bool parallel(const Line<T>& l1, const Line<T>& l2) {
	return cross(l1.b - l1.a, l2.b - l2.a) == 0;
}

template<class T>
f64 distancePP(const Point<T>& a, const Point<T>& b) {
	return length(a - b);
}

template<class T>
f64 distancePL(const Point<T>& p, const Line<T>& l) {
	return 1.L * std::abs(cross(l.a - l.b, l.a - p)) / length(l);
}

template<class T>
f64 distancePS(const Point<T>& p, const Line<T>& l) {
	if (dot(p - l.a, l.b - l.a) < 0) {
		return distance(p, l.a);
	}
	if (dot(p - l.b, l.a - l.b) < 0) {
		return distance(p, l.b);
	}
	return distancePL(p, l);
}

template<class T>
Point<T> rotate(const Point<T>& p) {
	return Point<T>(-p.y, p.x);
}

template<class T>
int sgn(const Point<T>& a) {
	return a.y > 0 or (a.y == 0 and a.x > 0) ? 1 : -1;
}

template<class T>
bool PointOnLineLeft(const Point<T>& p, const Line<T>& l) {
	return cross(l.b - l.a, p - l.a) > 0;
}

template<class T>
Point<T> LineIntersection(const Line<T>& l1, const Line<T>& l2) {
	return l1.a + (l1.b - l1.a) * (cross(l2.b - l2.a, l1.a - l2.a) / cross(l2.b - l2.a, l1.a - l1.b));
}

template<class T>
bool PointOnSegment(const Point<T>& p, const Line<T>& l) {
	return cross(l.b - l.a, p - l.a) == 0 and std::min(l.a.x, l.b.x) <= p.x and p.x <= std::max(l.a.x, l.b.x) and std::min(l.a.y, l.b.y) <= p.y and p.y <= std::max(l.a.y, l.b.y);
}

template<class T>
bool PointInPolygon(const Point<T>& a, const std::vector<Point<T>>& p) {
	int n = p.size();
	for (int i = 0; i < n; i += 1) {
		if (PointOnSegment(a, Line(p[i], p[(i + 1) % n]))) {
			return true;
		}
	}
	int t = 0;
	for (int i = 0; i < n; i += 1) {
		const auto & u = p[i], v = p[(i + 1) % n];
		if (u.x < a.x and v.x >= a.x and PointOnLineLeft(a, Line(v, u))) {
			t ^= 1;
		}
		if (u.x >= a.x and v.x < a.x and PointOnLineLeft(a, Line(u, v))) {
			t ^= 1;
		}
	}
	return t == 1;
}

// 0 : not intersect
// 1 : strictly intersect
// 2 : overlap
// 3 : intersect at endpoint
template<class T>
std::tuple<int, Point<T>, Point<T>> SegmentIntersection(const Line<T>& l1, const Line<T>& l2) {
	if (std::max(l1.a.x, l1.b.x) < std::min(l2.a.x, l2.b.x)) {
		return {0, Point<T>(), Point<T>()};
	}
	if (std::min(l1.a.x, l1.b.x) > std::max(l2.a.x, l2.b.x)) {
		return {0, Point<T>(), Point<T>()};
	}
	if (std::max(l1.a.y, l1.b.y) < std::min(l2.a.y, l2.b.y)) {
		return {0, Point<T>(), Point<T>()};
	}
	if (std::min(l1.a.y, l1.b.y) > std::max(l2.a.y, l2.b.y)) {
		return {0, Point<T>(), Point<T>()};
	}
	if (cross(l1.b - l1.a, l2.b - l2.a) == 0) {
		if (cross(l1.b - l1.a, l2.a - l1.a) != 0) {
			return {0, Point<T>(), Point<T>()};
		} else {
			const auto& maxx1 = std::max(l1.a.x, l1.b.x);
			const auto& minx1 = std::min(l1.a.x, l1.b.x);
			const auto& maxy1 = std::max(l1.a.y, l1.b.y);
			const auto& miny1 = std::min(l1.a.y, l1.b.y);
			const auto& maxx2 = std::max(l2.a.x, l2.b.x);
			const auto& minx2 = std::min(l2.a.x, l2.b.x);
			const auto& maxy2 = std::max(l2.a.y, l2.b.y);
			const auto& miny2 = std::min(l2.a.y, l2.b.y);
			Point<T> p1(std::max(minx1, minx2), std::max(miny1, miny2));
			Point<T> p2(std::min(maxx1, maxx2), std::min(maxy1, maxy2));
			if (not PointOnSegment(p1, l1)) {
				std::swap(p1.y, p2.y);
			}
			if (p1 == p2) {
				return {3, p1, p2};
			} else {
				return {2, p1, p2};
			}
		}
	}
	const auto& cp1 = cross(l2.a - l1.a, l2.b - l1.a);
	const auto& cp2 = cross(l2.a - l1.b, l2.b - l1.b);
	const auto& cp3 = cross(l1.a - l2.a, l1.b - l2.a);
	const auto& cp4 = cross(l1.a - l2.b, l1.b - l2.b);

	if ((cp1 > 0 and cp2 > 0) or (cp1 < 0 and cp2 < 0) or (cp3 > 0 and cp4 > 0) or (cp3 < 0 and cp4 < 0)) {
		return {0, Point<T>(), Point<T>()};
	}

	Point p = LineIntersection(l1, l2);
	if (cp1 != 0 and cp2 != 0 and cp3 != 0 and cp4 != 0) {
		return {1, p, p};
	} else {
		return {3, p, p};
	}
}

template<class T>
f64 distanceSS(const Line<T>& l1, const Line<T>& l2) {
	if (std::get<0>(SegmentIntersection(l1, l2)) != 0) {
		return 0.L;
	}
	return std::min({distancePS(l1.a, l2), distancePS(l1.b, l2), distancePS(l2.a, l1), distancePS(l2.b, l1)});
}

template<class T>
bool SegmentInPolygon(const Line<T>& l, const std::vector<Point<T>>& p) {
	int n = p.size();
	if ((not PointInPolygon(l.a, p)) or (not PointInPolygon(l.b, p))) {
		return false;
	}
	for (int i = 0; i < n; i += 1) {
		const auto & u = p[i], v = p[(i + 1) % n], w = p[(i + 2) % n];
		const auto & [t, p1, p2] = SegmentIntersection(l, Line(u, v));
		if (t == 1) {
			return false;
		}
		if (t == 0) {
			continue;
		}
		if (t == 2) {
			if (PointOnSegment(v, l) and v != l.a and v != l.b and cross(v - u, w - v) > 0) {
				return false;
			}
		} else {
			if (p1 != u && p1 != v) {
				if (PointOnLineLeft(l.a, Line(v, u)) or PointOnLineLeft(l.b, Line(v, u))) {
					return false;
				}
			} else if (p1 == v) {
				if (l.a == v) {
					if (PointOnLineLeft(u, l)) {
						if (PointOnLineLeft(w, l) and PointOnLineLeft(w, Line(u, v))) {
							return false;
						}
					} else {
						if (PointOnLineLeft(w, l) or PointOnLineLeft(w, Line(u, v))) {
							return false;
						}
					}
				} else if (l.b == v) {
					if (PointOnLineLeft(u, Line(l.b, l.a))) {
						if (PointOnLineLeft(w, Line(l.b, l.a)) and PointOnLineLeft(w, Line(u, v))) {
							return false;
						}
					} else {
						if (PointOnLineLeft(w, Line(l.b, l.a)) or PointOnLineLeft(w, Line(u, v))) {
							return false;
						}
					}
				} else {
					if (PointOnLineLeft(u, l)) {
						if (PointOnLineLeft(w, Line(l.b, l.a)) or PointOnLineLeft(w, Line(u, v))) {
							return false;
						}
					} else {
						if (PointOnLineLeft(w, l) or PointOnLineLeft(w, Line(u, v))) {
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}

template<class T>
std::vector<Point<T>> hp(std::vector<Line<T>> lines) {
	std::sort(lines.begin(), lines.end(), [&](const auto & l1, const auto & l2) {
		const auto & d1 = l1.b - l1.a, d2 = l2.b - l2.a;
		if (sgn(d1) != sgn(d2)) {
			return sgn(d1) == 1;
		}
		return cross(d1, d2) > 0;
	});
	std::deque<Point<T>>ps;
	std::deque<Line<T>>ls;
	for (const auto & l : lines) {
		if (ls.empty()) {
			ls.push_back(l);
			continue;
		}
		while (not ps.empty() and not PointOnLineLeft(ps.back(), l)) {
			ps.pop_back();
			ls.pop_back();
		}
		while (not ps.empty() and not PointOnLineLeft(ps[0], l)) {
			ps.pop_front();
			ls.pop_front();
		}
		if (cross(l.b - l.a, ls.back().b - ls.back().a) == 0) {
			if (dot(l.b - l.a, ls.back().b - ls.back().a) > 0 and not PointOnLineLeft(ls.back().a, l)) {
				// assert(ls.size() == 1);
				ls[0] = l;
			}
			return {};
		}
		ps.push_back(LineIntersection(ls.back(), l));
		ls.push_back(l);
	}
	while (not ps.empty() and not PointOnLineLeft(ps.back(), ls[0])) {
		ps.pop_back();
		ls.pop_back();
	}
	if (ls.size() <= 2) {
		return {};
	}
	ps.push_back(LineIntersection(ls[0], ls.back()));
	return std::vector(ps.begin(), ps.end());
}

template<class T>
std::vector<Point<T>> getHull(std::vector<Point<T>> p) {
	std::vector<Point<T>>h, l;
	std::sort(p.begin(), p.end(), [&](const auto & a, const auto & b) {
		return a.x == b.x ? a.y < b.y : a.x < b.x;
	});
	p.erase(std::unique(p.begin(), p.end()), p.end());
	if (p.size() <= 1) {
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

template<class T>
T getLongest(const std::vector<Point<T>>& ret) {
	std::vector<Point<T>> p = getHull(ret);
	if (p.size() <= 2) {
		return square(p[0] - p.back());
	}
	int n = p.size();
	T ans = T();
	for (int i = 0, j = 2; i < n; i += 1) {
		while (std::abs(cross(p[(i + 1) % n] - p[i], p[j] - p[i])) <= std::abs(cross(p[(i + 1) % n] - p[i], p[(j + 1) % n] - p[i]))) {
			j = (j + 1) % n;
		}
		ans = std::max({ans, square(p[i] - p[j]), square(p[(i + 1) % n] - p[j])});
	}
	return ans;
}

template<class T>
T PolygonArea(const std::vector<Point<T>>& p) {
	T res = 0;
	int n = p.size();
	for (int i = 0; i < n; i += 1) {
		const auto & u = p[i], v = p[(i + 1) % n];
		res += cross(u, v);
	}
	return res / 2;
}
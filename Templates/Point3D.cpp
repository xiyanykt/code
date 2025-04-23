template<class T>
struct Point {
	T x;
	T y;
	T z;
	Point(const T& _x = 0, const T& _y = 0, const T& _z = 0): x(_x), y(_y), z(_z) {}

	Point &operator+=(const Point& t)& {
		x += t.x;
		y += t.y;
		z += t.z;
		return *this;
	}
	Point &operator-=(const Point& t)& {
		x -= t.x;
		y -= t.y;
		z -= t.z;
		return *this;
	}
	Point &operator*=(const T& v)& {
		x *= v;
		y *= v;
		z *= v;
		return *this;
	}
	Point &operator/=(const T& v)& {
		x /= v;
		y /= v;
		z /= v;
		return *this;
	}
	Point operator-()const {
		return Point(-x, -y, -z);
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
	constexpr friend Point operator*(const T& v, Point a) {
		return a *= v;
	}
	constexpr friend Point operator/(Point a, const T& v) {
		return a /= v;
	}
	constexpr friend bool operator==(const Point& lsh, const Point& rsh) {
		return lsh.x == rsh.x and lsh.y == rsh.y and lsh.z == rsh.z;
	}
	friend std::istream &operator>>(std::istream &is, Point &p) {
		return is >> p.x >> p.y >> p.z;
	}
	friend std::ostream &operator<<(std::ostream &os, const Point &p) {
		return os << "(" << p.x << ", " << p.y << ", " << p.z << ")";
	}
};

template<class T>
T dot(const Point<T>& a, const Point<T>& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

template<class T>
T square(const Point<T>& p) {
	return dot(p, p);
}

template<class T>
T length(const Point<T>& p) {
	return std::sqrt(square(p));
}

template<class T>
Point<T> cross(const Point<T>& a, const Point<T>& b) {
	return Point(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

template<class T>
bool threePointcollinear(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
	return cross(b - a, c - a) == Point<T>();
}

template<class T>
bool Coplanar(const Point<T>& a, const Point<T>& b, const Point<T>& c, const Point<T>& d) {
	return dot(b - a, cross(c - a, d - a)) == 0;
}

using P = Point<f64>;
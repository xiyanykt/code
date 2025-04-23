#define P std::pair<f64, f64>
#define L std::pair<P, P>
#define x first
#define y second
#define a first
#define b second

std::istream& operator>>(std::istream& is, P& p) {
    int x, y;
    is >> x >> y;
    p = {x, y};
    return is;
}

P operator+(const P& a, const P& b) {
    return {a.x + b.x, a.y + b.y};
}
 
P operator-(const P& a, const P& b) {
    return {a.x - b.x, a.y - b.y};
}
 
P operator*(const P& a, auto v) {
    return {a.x * v, a.y * v};
}
 
P operator/(const P& a, auto v) {
    return {a.x / v, a.y / v};
}
 
P rotate(const P& p) {
    return {-p.y, p.x};
}
 
auto cross(const P& a, const P& b) {
    return a.x * b.y - a.y * b.x;
}
 
auto dot(const P& a, const P& b) {
    return a.x * b.x + a.y * b.y;
}
 
auto square(const P& a) {
    return dot(a, a);
}
 
int sgn(const P& p) {
    return p.y > 0 || p.y == 0 && p.x > 0 ? 1 : -1;
}
 
auto length(const P& p) {
    return std::sqrtl(square(p));
}

P lineIntersection(const L& l1, const L& l2) {
    return l1.a + (l1.b - l1.a) * cross(l2.b - l2.a, l1.a - l2.a) / cross(l2.b - l2.a, l1.a - l1.b); 
}

bool pointOnSegment(const P& p, const L& l) {
    return cross(p - l.a, l.b - l.a) == 0 && std::min(l.a.x, l.b.x) <= p.x && 
        p.x <= std::max(l.a.x, l.b.x) && std::min(l.a.y, l.b.y) <= p.y && p.y <= std::max(l.a.y, l.b.y);
}

int pointOnLineLeft(const P& p, const L& l) {
    auto c = cross(l.b - l.a, p - l.a);
    return c == 0 ? 0 : 1;
}

// 0 : not intersect
// 1 : strictly intersect
// 2 : overlap
// 3 : intersect at endpoint
std::tuple<int, P, P> segmentIntersection(const L& l1, const L& l2) {
    if (std::max(l1.a.x, l1.b.x) < std::min(l2.a.x, l2.b.x)) {
        return {0, P(), P()};
    }
    if (std::max(l2.a.x, l2.b.x) < std::min(l1.a.x, l1.b.x)) {
        return {0, P(), P()};
    }
    if (std::max(l1.a.y, l1.b.y) < std::min(l2.a.y, l2.b.y)) {
        return {0, P(), P()};
    }
    if (std::max(l2.a.y, l2.b.y) < std::min(l1.a.y, l1.b.y)) {
        return {0, P(), P()};
    }
    if (cross(l1.b - l1.a, l2.b - l2.a) == 0) {
        if (cross(l1.b - l1.a, l2.a - l1.a) != 0) {
            return {0, P(), P()};
        } else {
            const auto maxX1 = std::max(l1.a.x, l1.b.x);
            const auto minX1 = std::min(l1.a.x, l1.b.x);
            const auto maxY1 = std::max(l1.a.y, l1.b.y);
            const auto minY1 = std::min(l1.a.y, l1.b.y);
            const auto maxX2 = std::max(l2.a.x, l2.b.x);
            const auto minX2 = std::min(l2.a.x, l2.b.x);
            const auto maxY2 = std::max(l2.a.y, l2.b.y);
            const auto minY2 = std::min(l2.a.y, l2.b.y);
            P p1(std::max(minX1, minX2), std::max(minY1, minY2));
            P p2(std::min(maxX1, maxX2), std::min(maxY1, maxY2));
            if (!pointOnSegment(p1, l1)) {
                std::swap(p1.y, p2.y);
            }
            if (p1 == p2) {
                return {3, p1, p2};
            } else {
                return {2, p1, p2};
            }
        }
    }
    const auto cr1 = cross(l2.a - l1.a, l2.b - l1.a);
    const auto cr2 = cross(l2.a - l1.b, l2.b - l1.b);
    const auto cr3 = cross(l1.a - l2.a, l1.b - l2.a);
    const auto cr4 = cross(l1.a - l2.b, l1.b - l2.b);
    if ((cr1 > 0 && cr2 > 0) || (cr1 < 0 && cr2 < 0) || (cr3 > 0 && cr4 > 0) || (cr3 < 0 && cr4 < 0)) {
        return {0, P(), P()};
    }
    P p = lineIntersection(l1, l2);
    if (cr1 != 0 && cr2 != 0 && cr3 != 0 && cr4 != 0) {
        return {1, p, p};
    } else {
        return {3, p, p};
    }
}

auto gethull(std::vector<P> p) {
    if (p.size() <= 1) {
        return p;
    }
    int n = p.size();
    for (int i = 1; i < n; i += 1) {
        if (p[i].y < p[0].y || p[i].y == p[0].y && p[i].x < p[0].x) {
            std::swap(p[i], p[0]);
        }
    }
 
    std::sort(p.begin() + 1, p.end(), [&](const P& u, const P& v) {
        auto a = u - p[0], b = v - p[0];
        if (sgn(a) == sgn(b)) {
            return cross(a, b) > 0;
        }
        return sgn(a) > sgn(b);
    });
 
    std::vector<P>stk{p[0]};
    for (int i = 1; i < n; i += 1) {
        while (stk.size() > 1 && cross(stk.back() - stk.end()[-2], p[i] - stk.back()) <= 0) {
            stk.pop_back();
        }
        stk.push_back(p[i]);
    }
    return stk;
}
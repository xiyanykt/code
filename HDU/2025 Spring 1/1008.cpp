#include<bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f64 = long double;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

#ifndef ONLINE_JUDGE
#include "algo/debug.hpp"
#else
#define debug(...) (void)42
#endif

template<class T>
constexpr bool chmax(T& x, T y) {
    if (y > x) {
        x = y;
        return true;
    }
    return false;
}

template<class T>
constexpr bool chmin(T& x, T y) {
    if (y < x) {
        x = y;
        return true;
    }
    return false;
}

using Point = std::pair<f64, f64>;
#define x first
#define y second

Point operator+(const Point& a, const Point& b) {
    return {a.x + b.x, a.y + b.y};
}

Point operator-(const Point& a, const Point& b) {
    return {a.x - b.x, a.y - b.y};
}

Point operator*(const Point& a, f64 m) {
    return {a.x * m, a.y * m};
}

Point operator/(const Point& a, f64 m) {
    return {a.x / m, a.y / m};
}

f64 dot(const Point& a, const Point& b) {
    return a.x * b.x + a.y * b.y;
}

f64 cross(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

f64 length(const Point& a) {
    return sqrtl(dot(a, a));
}

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
auto work(std::vector<Point> p) {
    for (int t = 0; t < 7; t += 1) {
        std::shuffle(p.begin(), p.end(), rng);
    }
    int n = p.size();
    f64 r {};
    Point o = p[0];

    auto circumcenter = [&](const Point& a, const Point& b, const Point& c) {
        f64 d = 2.L * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
        assert(d != 0);
        Point p {};
        p.x = (dot(a, a) * (b.y - c.y) + dot(b, b) * (c.y - a.y) + dot(c, c) * (a.y - b.y)) / d;
        p.y = (dot(a, a) * (c.x - b.x) + dot(b, b) * (a.x - c.x) + dot(c, c) * (b.x - a.x)) / d;
        return p;
    };

    for (int i = 1; i < n; i += 1) {
        if (length(o - p[i]) > r) {
            o = p[i];
            r = {0};
            for (int j = 0; j < i; j += 1) {
                if (length(o - p[j]) > r) {
                    o = (p[i] + p[j]) * 0.5L;
                    r = length(o - p[i]);
                    for (int k = 0; k < j; k += 1) {
                        if (length(o - p[k]) > r) {
                            o = circumcenter(p[i], p[j], p[k]);
                            r = length(o - p[i]);
                        }
                    }
                }
            }
        }
    }
    return std::pair(r, o);
}

constexpr f64 pi = std::acos(-1.L);

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto solve = [&]() {
        int n;
        std::cin >> n;

        std::vector<Point>p(n);
        for (auto & [x, y] : p) {
            int a, b;
            std::cin >> a >> b;
            x = a, y = b;
        }

        auto [r, o] = work(p);
        auto [x, y] = o;

        f64 s = 0;
        for (int i = 0; i < n; i += 1) {
            s += cross(p[i], p[(i + 1) % n]);
        }
        s = std::abs(s) / 2;

        s = pi * r * r - s;
        s /= 2 * pi * r;

        std::cout << std::fixed << std::setprecision(6) << s << '\n';
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
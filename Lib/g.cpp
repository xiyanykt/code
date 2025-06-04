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
#define debug(...) (void)13
#endif

template<class T>
constexpr bool chmax (T& x, T y) {
    if (y > x) {
        x = y;
        return true;
    }
    return false;
}

template<class T>
constexpr bool chmin (T& x, T y) {
    if (y < x) {
        x = y;
        return true;
    }
    return false;
}

#define P std::pair<i64, i64>
#define x first
#define y second

P operator+(P a, P b) {
    return {a.x + b.x, a.y + b.y};
}

P operator-(P a, P b) {
    return {a.x - b.x, a.y - b.y};
}

auto cross(P a, P b) {
    return a.x * b.y - a.y * b.x;
}

auto dot(P a, P b) {
    return a.x * b.x + a.y * b.y;
}

int sgn(P a) {
    return (a.y > 0 || (a.y == 0 && a.x > 0)) ? 1 : -1;
}

auto hull(std::vector<P> p) {
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

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;

    std::vector<P>p(n);
    for (auto& [x, y] : p) {
        std::cin >> x >> y;
    }

    i64 ans = 0;
    auto h = hull(p);
    int m = h.size();
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            for (int k = 0; k < m; k += 1) {
                chmin(ans, dot(h[j] - p[i], h[k] - p[i]));
                chmin(ans, dot(p[i] - h[j], p[i] - h[k]));
            }
        }
    }

    std::cout << ans << '\n';
    return 0;
}
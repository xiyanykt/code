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

template<class T, auto f, auto e>
struct SegmentTree {
    int n;
    std::vector<T> s;
    SegmentTree(int n) : n(n), s(n * 2, e()) {}
    void set(int i, T v) {
        for (s[i += n] = v; i /= 2;) s[i] = f(s[i * 2], s[i * 2 + 1]);
    }
    /// Returns the product of elements in [l, r).
    T product(int l, int r) {
        T rl = e(), rr = e();
        for (l += n, r += n; l != r; l /= 2, r /= 2) {
            if (l % 2) rl = f(rl, s[l++]);
            if (r % 2) rr = f(s[r -= 1], rr);
        }
        return f(rl, rr);
    }
};

constexpr int K = 5;
constexpr i64 inf = 1E18;
using Matrix = std::array<std::array<i64, K>, K>;
struct Info {
    Matrix m {};

    Info () {
        for (auto & c : m) {
            c.fill(-inf);
        }
        m[0][0] = m[2][2] = m[4][4] = 0;
    }

    Info (i64 a, i64 b) {
        for (auto & c : m) {
            c.fill(-inf);
        }
        m[0][0] = m[2][2] = m[4][4] = 0;
        m[1][1] = m[3][3] = a;
        m[0][2] = m[2][4] = a + 2 * b;
        m[0][1] = m[2][3] = m[1][2] = m[3][4] = a + b;
    }

    friend Info operator+(const Info& a, const Info& b) {
        Info c{};
        for (int k = 0; k < K; k += 1) {
            for (int i = 0; i < K; i += 1) {
                for (int j = 0; j < K; j += 1) {
                    chmax(c.m[i][j], a.m[i][k] + b.m[k][j]);
                }
            }
        }
        return c;
    }
};

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int>a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i += 1) {
        std::cin >> a[i];
    }

    for (int i = 1; i <= n; i += 1) {
        std::cin >> b[i];
    }

    SegmentTree<Info, [](Info a, Info b) { return a + b; }, []() { return Info{}; }>seg(n + 1);
    for (int i = 1; i <= n; i += 1) {
        seg.set(i, Info(a[i], b[i]));
    }

    int q;
    std::cin >> q;
    while (q--) {
        int o;
        std::cin >> o;
        if (o == 1) {
            int p, x;
            std::cin >> p >> x;
            a[p] = x;
            seg.set(p, Info(a[p], b[p]));
        } else if (o == 2) {
            int p, x;
            std::cin >> p >> x;
            b[p] = x;
            seg.set(p, Info(a[p], b[p]));
        } else {
            int l, r;
            std::cin >> l >> r;
            std::cout << seg.product(l, r + 1).m[0][4] << '\n';
        }
    }
    return 0;
}

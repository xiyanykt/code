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

template <class T, auto f>
struct SparseTable {
    std::vector<std::vector<T>>jump;

    SparseTable() = default;
    SparseTable(const std::vector<T>& a) {
        int n = a.size() - 1;
        int m = std::__lg(n);
        jump.assign(m + 1, std::vector<T>(n + 1));
        std::copy(a.begin(), a.end(), jump[0].begin());
        for (int j = 1; j <= m; j += 1) {
            for (int i = 1; i + (1 << (j - 1)) - 1 <= n; i += 1) {
                jump[j][i] = f(jump[j - 1][i], jump[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    constexpr T rangeQuery(int l, int r) const {
        assert(l <= r);
        int k = std::__lg(r - l + 1);
        return f(jump[k][l], jump[k][r - (1 << k) + 1]);
    }
};

constexpr int bitOr(int a, int b) {
    return (a | b);
}

constexpr int bitAnd(int a, int b) {
    return (a & b);
}

// template<class T, auto f = [](T a, T b) { return a + b; }, auto e = []() { return T(); }>
using T = i64;
constexpr i64 inf = 1E18;

auto f(i64 a, i64 b) {
    return std::max(a, b);
}

auto e() {
    return -inf;
}

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

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto solve = [&]() {
        int n, m;
        std::cin >> n >> m;

        std::vector a(n + 1, 0);
        for (int i = 1; i <= n; i += 1) {
            std::cin >> a[i];
        }

        std::vector g(1 << m, 0LL);
        for (int x = 0; x < (1 << m); x += 1) {
            std::cin >> g[x];
        }

        std::vector p(m, std::vector(n + 1, 0));
        for (int k = 0; k < m; k += 1) {
            for (int i = 2; i <= n; i += 1) {
                if ((a[i] >> k & 1) == (a[i - 1] >> k & 1)) {
                    p[k][i] = p[k][i - 1];
                } else {
                    p[k][i] = i - 1;
                }
            }
        }

        auto s1 = SparseTable<int, bitOr>(a);
        auto s2 = SparseTable<int, bitAnd>(a);
        auto work = [&](int l, int r) {
            return s1.rangeQuery(l, r) - s2.rangeQuery(l, r);
        };

        // SegmentTree<i64, [](i64 a, i64 b) { return std::max(a, b); }, []() { return -inf; }>seg(n + 1);
        SegmentTree seg(n + 1);
        seg.set(0, 0);
        for (int i = 1; i <= n; i += 1) {
            std::vector<int>t{0, i};
            for (int k = 0; k < m; k += 1) {
                t.push_back(p[k][i]);
            }

            i64 w = -inf;
            std::sort(t.begin(), t.end());
            t.erase(std::unique(t.begin(), t.end()), t.end());
            for (int j = 1; j < t.size(); j += 1) {
                int x = t[j - 1] + 1, y = t[j];
                chmax(w, seg.product(x - 1, y) + g[work(y, i)]);
            }
            seg.set(i, w);
        }

        std::cout << seg.product(n, n + 1) << '\n';
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
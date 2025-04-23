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

template<class T, auto f = [](T a, T b) { return a + b; }, auto e = []() { return T(); }>
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
        int n;
        std::cin >> n;

        std::vector<int>a(n + 1);
        for (int i = 1; i <= n; i += 1) {
            std::cin >> a[i];
        }

        constexpr int inf = 1E9;
        std::pair<int, std::pair<int, int>>res {inf, {0, 0}};

        const int x = std::ranges::max(a) + 1;
        for (int r = n; r >= 1; r -= 1) {
            SegmentTree<int>seg(x + 1);
            for (int l = r; l >= 1; l -= 1) {
                int cnt = seg.product(a[l] + 1, x + 1) - seg.product(1, a[l]);
                int v = seg.product(a[l], a[l] + 1);
                seg.set(a[l], v + 1);
                chmin(res, {cnt, {l, r}});
            }
        }

        auto [c, v] = res;
        auto [l, r] = v;
        std::cout << l << ' ' << r << '\n';
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
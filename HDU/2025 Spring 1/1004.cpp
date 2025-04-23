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

constexpr int fMax(int a, int b) {
    return std::max(a, b);
}

constexpr int fMin(int a, int b) {
    return std::min(a, b);
}

constexpr int Mod = 1E9 + 7;

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto solve = [&]() {
        int n, q;
        std::cin >> n >> q;

        constexpr int inf = 2E9;
        std::vector<int>a(n + 1);
        for (int i = 1; i <= n; i += 1) {
            std::cin >> a[i];
        }

        SparseTable<int, fMax>rmax[2];
        SparseTable<int, fMin>rmin[2];
        std::vector x(n + 1, -inf), y(n + 1, -inf);
        for (int i = 1; i <= n; i += 1) {
            (i % 2 == 1 ? x : y)[i] = a[i];
        }
        rmax[0] = SparseTable<int, fMax>(y);
        rmax[1] = SparseTable<int, fMax>(x);
        x = std::vector(n + 1, inf), y = std::vector(n + 1, inf);
        for (int i = 1; i <= n; i += 1) {
            (i % 2 == 1 ? x : y)[i] = a[i];
        }
        rmin[0] = SparseTable<int, fMin>(y);
        rmin[1] = SparseTable<int, fMin>(x);

        std::vector<int>f(n + 1), w(n + 1);
        for (int l = 1, r = 1; r <= n; r += 1) {
            for (; l <= r && (!(rmax[0].rangeQuery(l, r) < rmin[1].rangeQuery(l, r) || rmax[1].rangeQuery(l, r) < rmin[0].rangeQuery(l, r))); l += 1) {
                ;
            }
            f[r] = l;
            w[r] = r - l + 1;
        }

        debug(f);
        debug(w);

        int ans = 0;
        auto s = SparseTable<int, fMax>(w);
        for (int i = 1; i <= q; i += 1) {
            int res = 0;
            int l, r;
            std::cin >> l >> r;

            int k = std::lower_bound(f.begin() + l, f.begin() + r + 1, l) - f.begin();
            res = k - l;
            if (k <= r) {
                chmax(res, s.rangeQuery(k, r));
            }
            ans = (1LL * ans + 1LL * res * i % Mod) % Mod;
        }

        std::cout << ans << '\n';
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
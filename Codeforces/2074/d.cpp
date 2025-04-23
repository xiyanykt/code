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

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto solve = [&]() {
        int n, m;
        std::cin >> n >> m;

        std::vector x(n + 1, 0), r(n + 1, 0);
        for (int i = 1; i <= n; i += 1) {
            std::cin >> x[i];
        }

        for (int i = 1; i <= n; i += 1) {
            std::cin >> r[i];
        }

        std::map<int, std::vector<std::pair<int, int>>>h;
        for (int i = 1; i <= n; i += 1) {
            for (int y = 0; y <= r[i]; y += 1) {
                int d = sqrtl(1LL * r[i] * r[i] - 1LL * y * y);
                int l = x[i] - d, r = x[i] + d;
                h[y].push_back({l, r});
                if (y >= 1) {
                    h[-y].push_back({l, r});
                }
            }
        }

        i64 res = 0;
        for (auto [y, v] : h) {
            std::sort(v.begin(), v.end());
            auto [fl, fr] = v[0];
            for (int i = 1; i < v.size(); i += 1) {
                auto [l, r] = v[i];
                if (l <= fr + 1) {
                    chmax(fr, r);
                } else {
                    res += fr - fl + 1;
                    fl = l;
                    fr = r;
                }
            }
            res += fr - fl + 1;
        }

        std::cout << res << '\n';
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
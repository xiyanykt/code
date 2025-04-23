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
        int n;
        std::cin >> n;

        std::vector<int>a(n + 1);
        for (int i = 1; i <= n; i += 1) {
            std::cin >> a[i];
        }

        std::sort(a.begin() + 1, a.end());
        
        int h = n / 2;
        auto l = std::vector<int>{a.begin() + 1, a.begin() + h + 1};
        auto r = std::vector<int>{a.begin() + h + 1, a.end()};
        int x = l[h / 2 - 1], y = r[h / 2 - 1];
        
        i64 res = std::numeric_limits<i64>::max();
        for (const auto & u : {x - 1, x, x + 1}) {
            for (const auto & v : {y - 1, y, y + 1}) {
                if (u == v) {
                    continue;
                }
                i64 cur = 0;
                for (const auto & e : l) {
                    cur += std::abs(e - u);
                }
                for (const auto & e : r) {
                    cur += std::abs(e - v);
                }
                chmin(res, cur);
            }
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

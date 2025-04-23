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
        int k;
        std::cin >> k;

        constexpr int inf = 1E9;
        if (k == 0) {
            std::cout << 0 << '\n';
        } else {
            int lo = 1, hi = 1E9;
            while (lo <= hi) {
                int mid = (lo + hi) >> 1;
                if (1LL * mid * (mid - 1) / 2 < k) {
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
            lo -= 1;
            // debug(lo * (lo - 1) / 2, k);

            std::vector<std::pair<int, int>>res;
            for (int i = 1; i <= lo; i += 1) {
                res.push_back({0, i});
            }

            assert(!res.empty());
            int w = inf;
            int d = k - 1LL * lo * (lo - 1) / 2;
            
            int i = 0;
            while (d >= 1) {
                assert(i < res.size());
                auto [x, y] = res[i];
                if (d == 1) {
                    d -= 1;
                    res.push_back({w--, y});
                    break;
                }
                int lo = 1, hi = 1E9;
                while (lo <= hi) {
                    int mid = (lo + hi) >> 1;
                    if (1LL * mid * (mid - 1) / 2 < d) {
                        lo = mid + 1;
                    } else {
                        hi = mid - 1;
                    }
                }
                lo -= 1;
                for (int c = 1; c <= lo - 1; c += 1) {
                    auto [x, y] = res[i];
                    res.push_back({w--, y});
                }
                i += 1;
                d -= 1LL * lo * (lo - 1) / 2;
            }
            assert(d == 0);
            assert(int(res.size()) <= 500);
            std::cout << res.size() << '\n';
            for (const auto & [x, y] : res) {
                std::cout << x << ' ' << y << '\n';
            }
        }
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
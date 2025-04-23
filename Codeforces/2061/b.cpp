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

        std::map<int, int>rec;
        for (int i = 1; i <= n; i += 1) {
            rec[a[i]] += 1;
        }

        int cnt = 0, cof = 0;
        std::ranges::sort(a);        
        for (const auto & [x, v] : rec) {
            if (v >= 4) {
                std::cout << std::format("{} {} {} {}\n", x, x, x, x);
                return ;
            } else if (v >= 3) {
                if (x != a[1]) {
                    std::cout << x << ' ' << x << ' ' << x << ' ' << a[1] << '\n';
                    return ;
                }
                int p = std::ranges::upper_bound(a, x) - a.begin();
                if (a[p] < 3 * x) {
                    std::cout << x << ' ' << x << ' ' << x << ' ' << a[p] << '\n';
                    return ;
                }
                cnt += 1;
                cof = x;
            } else if (v >= 2) {
                if (cnt >= 1) {
                    std::cout << std::format("{} {} {} {}\n", cof, cof, x, x);
                    return ;
                }
                cnt += 1;
                cof = x;
            }
        }

        if (cnt != 0) {
            std::vector<int>b;
            for (int i = 1; i <= n; i += 1) {
                if (a[i] == cof) {
                    continue;
                }
                b.push_back(a[i]);
            }
            for (int i = 1; i < b.size(); i += 1) {
                int x = b[i - 1], y = b[i];
                if (x + 2 * cof > y) {
                    std::cout << cof << ' ' << cof << ' ' << x << ' ' << y << '\n';
                    return ;
                }
            }
        }

        std::cout << -1 << '\n';
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
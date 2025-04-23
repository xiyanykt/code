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

        std::vector<int>a(n + 1), b(n + 1);
        for (int i = 1; i <= n; i += 1) {
            std::cin >> a[i];
        }

        for (int i = 1; i <= n; i += 1) {
            std::cin >> b[i];
        }

        int x = 0, y = 1E9, c = 0;
        for (int i = 1; i <= n; i += 1) {
            if (a[i] >= b[i]) {
                chmin(y, a[i] - b[i]);
            } else {
                c += 1;
                x += b[i] - a[i];
            }
        }

        std::cout << (x <= y && c <= 1 ? "YES\n" : "NO\n");
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
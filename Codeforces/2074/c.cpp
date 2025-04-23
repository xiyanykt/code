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
        int x;
        std::cin >> x;

        if (x <= 2) {
            std::cout << -1 << '\n';
            return ;
        }

        int y = x;
        for (int k = 30; k >= 0; k -= 1) {
            if (x >> k & 1) {
                y ^= 1 << k;
                break;
            }
        }

        for (int k = 0; k <= 30; k += 1) {
            if (~x >> k & 1) {
                y |= 1 << k;
                break;
            }
        }

        int z = x ^ y;
        debug(x, y, z);
        if (y >= 1 && y <= x && x + y > z && x + z > y && y + z > x) {
            std::cout << y << '\n';
        } else {
            std::cout << -1 << '\n';
        }
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
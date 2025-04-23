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

        std::string s;
        std::cin >> s;

        int r = 0, x = 0, p = 0;
        i64 d = 0;
        for (auto & c : s) {
            if (x) {
                r = p;
                x = 0;
            }
            if (c == '0') {
                r += 10;
            } else if (c == '1') {
                r = std::max(r - 5, 0);
            } else if (c == '2') {
                p = r;
                r = std::max(r - 10, 0);
                x = 1;
            }
            d += r;
        }
        std::cout << d << '\n';
    };

    int t = 1;
    // std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
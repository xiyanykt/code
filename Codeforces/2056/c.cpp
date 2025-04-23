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

        if (n == 6) {
            std::cout << "1 1 2 3 1 2\n";
            return ;
        }

        if (n == 7) {
            std::cout << "1 1 2 3 1 2 2\n";
            return ;
        }

        for (int i = 1; i <= n / 2; i += 1) {
            std::cout << i << ' ';
        }
        for (int i = 1; i <= n / 2; i += 1) {
            std::cout << i << ' ';
        }

        if (n % 2) {
            std::cout << n;
        }

        std::cout << '\n';
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
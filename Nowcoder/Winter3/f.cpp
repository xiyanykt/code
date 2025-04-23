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
        int n, a, b, c;
        std::cin >> n >> a >> b >> c;

        for (int a1 = 0; a1 <= n; a1 += 1) {
            for (int a2 = 0; a1 + a2 <= n; a2 += 1) {
                for (int a3 = 0; a1 + a2 + a3 <= n; a3 += 1) {
                    for (int a4 = 0; a1 + a2 + a3 + a4 <= n; a4 += 1) {
                        for (int a5 = 0; a1 + a2 + a3 + a4 + a5 <= n; a5 += 1){
                            int a6 = n - (a1 + a2 + a3 + a4 + a5);
                            if (a == a1 + a2 + a3 && b == a3 + a4 + a5 && c == a5 + a6 + a1) {
                                std::cout << "Yes\n";
                                return ;
                            }
                        }
                    }
                }
            }
        }

        std::cout << "No\n";
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
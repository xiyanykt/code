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

        std::string s, t;
        std::cin >> s >> t;
        std::array<int, 26> cnt {};
        for (auto &c : s) {
            cnt[c - 'a'] += 1;
        }
        for (auto &c : t) {      
            cnt[c - 'a'] -= 1;
        }

        int res = 0, dif = n - m;
        for (auto & c : cnt) {
            while (dif <= -2 && c <= -2) {
                c += 2;
                dif += 2;
            }
            while (dif >= 2 && c >= 2) {
                dif -= 2;
                c -= 2;
            }
        }

        for (auto& c : cnt) {
            res += std::abs(c);
        }

        std::cout << res / 2 << '\n';
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
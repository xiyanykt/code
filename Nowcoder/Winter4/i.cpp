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

    const std::string h = "uwawauwa";

    auto solve = [&]() {
        int n;
        std::cin >> n;

        std::string s;
        std::cin >> s;

        i64 res = 0;
        int cnt = 0;
        for (int i = 0; i < n; i += 1) {
            int y = h.size();
            if (i + y - 1 >= n) {
                break;
            }
            if (s.substr(i, y) == h) {
                res += cnt;
            }
            if (i) {
                cnt += s[i - 1] == 'u';
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
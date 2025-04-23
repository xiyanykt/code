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
        int l1, r1, l2, r2;
        std::cin >> l1 >> r1 >> l2 >> r2;

        i64 res = 0;
        i64 pre = 0;
        for (int k = 21; k >= 0; k -= 1) {
            int w = 1 << k;

            i64 cur = 0;
            if (r1 - l1 < w || r2 - l2 < w) {
                ;
            } else {
                int fl = (l1 + w - 1) / w;
                int fr = (r1 - w) / w;
                int gl = (l2 + w - 1) / w;
                int gr = (r2 - w) / w;
                cur = 1LL * std::max(0, fr - fl + 1) * std::max(0, gr - gl + 1);
            }
            res += cur - 4 * pre;
            pre = cur;
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
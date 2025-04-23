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
        int n, x;
        i64 k;
        std::cin >> n >> x >> k;

        std::string s;
        std::cin >> s;
        s = ' ' + s;

        int j = 0, h = 0;
        assert(x != 0);
        for (int i = 1; i <= n; i += 1) {
            if (x == 0) {
                j = i;
                break;
            }
            (s[i] == 'R' ? x += 1 : x -= 1);
        }
        if (x == 0 && j == 0) {
            j = n + 1;
        }

        x = 0;
        for (int i = 1; i <= n; i += 1) {
            (s[i] == 'R' ? x += 1 : x -= 1);
            if (x == 0) {
                h = i;
                break;
            }
        }

        i64 res = 0;
        if (j != 0) {
            
            j -= 1;
            k -= j;
            debug(k, j);
            res += 1;
            if (h != 0) {
                res += k / h;
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
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
#define debug(...) (void)13
#endif

template<class T>
constexpr bool chmax (T& x, T y) {
    if (y > x) {
        x = y;
        return true;
    }
    return false;
}

template<class T>
constexpr bool chmin (T& x, T y) {
    if (y < x) {
        x = y;
        return true;
    }
    return false;
}

void solve () {
    int n, m;
    std::cin >> n >> m;

    std::vector<int>a(n + 1);
    for (int i = 1; i <= n; i += 1) {
        std::cin >> a[i];
    }

    if (n >= 25) {
        std::cout << "YES\n";
    } else {
        std::map<std::pair<int, i64>, int>r;
        for (int s = 0; s < (1 << n); s += 1) {
            int c = __builtin_popcount(s);
            if (c <= n / 2) {
                i64 sum = 0;
                for (int i = 1; i <= n; i += 1) {
                    if (s >> (i - 1) & 1) {
                        sum += a[i];
                    }
                }
                if (r.count({c, sum}) && (s & r[{c, sum}]) == 0) {
                    std::cout << "YES\n";
                    return ;
                } else {
                    r[{c, sum}] = s;
                }
            }
        }
        std::cout << "NO\n";
    }
}

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
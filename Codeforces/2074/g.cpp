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

        std::vector a(n, 0);
        for (int i = 0; i < n; i += 1) {
            std::cin >> a[i];
        }

        std::vector f(n, std::vector(n, 0LL));
        for (int r = 0; r < n; r += 1) {
            for (int l = r - 2; l >= 0; l -= 1) {
                for (int k = l; k < r; k += 1) {
                    chmax(f[l][r], f[l][k] + f[k + 1][r]);
                }
                for (int k = l + 1; k < r; k += 1) {
                    i64 x = 1LL * a[l] * a[k] * a[r];
                    if (l + 1 < k - 1) {
                        x += f[l + 1][k - 1];
                    }
                    if (k + 1 < r - 1) {
                        x += f[k + 1][r - 1];
                    }
                    chmax(f[l][r], x);
                }
            }
        }

        std::cout << f[0].back() << '\n';
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
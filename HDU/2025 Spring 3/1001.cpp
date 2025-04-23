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

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // constexpr int N = 200;
    // int f[N + 1][N + 1];
    // f[0][0] = 1;
    // for (int n = 1; n <= 100; n += 1) {
    //     f[n][0] = 1;
    //     for (int m = 1; m <= n; m += 1) {
    //         f[n][m] = (f[n - 1][m - 1] + f[n - 1][m]) % 2;
    //     }
    // }

    // for (int n = 1; n <= 100; n += 1) {
    //     for (int m = 0; m <= n; m += 1) {
    //         if (f[n][m] % 2 == 1) {
    //             std::cout << std::format("n = {}, m = {}, bin(n) = {}, bin(m) = {}\n", n, m, std::bitset<8>(n).to_string(), std::bitset<8>(m).to_string());
    //         }
    //     }
    //     std::cout << std::endl;
    //     std::cout << std::endl;
    // }

    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;

        int ans = 1;
        constexpr int Mod = 998244353;
        std::vector<int>a(n + 1), l(n + 1);
        for (int i = 1; i <= n; i += 1) {
            std::cin >> a[i];
        }

        for (int i = 1; i <= n; i += 1) {
            std::cin >> l[i];
        }

        for (int i = 1; i <= n; i += 1) {
            std::vector<int>f;
            for (int k = 0; k <= 30; k += 1) {
                if (a[i] >> k & 1) {
                    f.push_back(1 << k);
                }
            }

            if (a[i] == 1) {
                ans = 1LL * ans * 2 % Mod;
                continue;
            }

            if ((a[i] & (a[i] - 1)) == 0) {
                ans = 1LL * ans * (1 + (l[i] >= a[i])) % Mod;
                continue;
            }
            
            int lo = 0, hi = (1 << __builtin_popcount(a[i])) - 1;
            while (lo <= hi) {
                int mid = (lo + hi) >> 1;
                int r = 0;
                for (int k = 0; k < int(f.size()); k += 1) {
                    if (mid >> k & 1) {
                        r |= f[k];
                    }
                }
                if (r <= l[i]) {
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
            // std::cout << lo << '\n';

            ans = 1LL * ans * lo % Mod;
        }
        std::cout << ans << '\n';
    }
    return 0;
}
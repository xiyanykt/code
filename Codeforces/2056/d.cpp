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

        std::vector<int>a(n + 1);
        for (int i = 1; i <= n; i += 1) {
            std::cin >> a[i];
        }

        i64 res = i64(n) * (n + 1) / 2;
        for (int x = 1; x <= 10; x += 1) {
            std::vector<int>b(n + 1);
            for (int i = 1; i <= n; i += 1) {
                b[i] = a[i] > x ? 1 : -1;
            }

            int sum = n;
            std::vector<int>p(n + 1);
            for (int i = 1; i <= n; i += 1) {
                p[i] = sum;
                sum += b[i];
            }

            std::vector<int>cnt(2 * n + 1);
            sum = n;
            for (int i = 1, j = 1; i <= n; i += 1) {
                if (a[i] == x) {
                    while (j <= i) {
                        cnt[p[j]] += 1;
                        j += 1;
                    }
                }
                sum += b[i];
                res -= cnt[sum];
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
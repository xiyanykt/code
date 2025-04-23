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

        std::vector a(n + 1, std::vector<int>(m + 1));
        for (int i = 1; i <= n; i += 1) {
            for (int j = 1; j <= m; j += 1) {
                std::cin >> a[i][j];
            }
            std::sort(a[i].begin() + 1, a[i].end());
        }

        std::vector<int>ord(n + 1);
        std::ranges::iota(ord, 0);
        std::sort(ord.begin() + 1, ord.end(), [&](const auto & i, const auto & j) {
            return a[i][1] < a[j][1];
        });

        for (int i = 2; i <= n; i += 1) {
            for (int j = 1; j <= m; j += 1) {
                if (a[ord[i]][j] < a[ord[i - 1]][j]) {
                    std::cout << -1 << '\n';
                    return ;
                }
            }
        }

        for (int j = 2; j <= m; j += 1) {
            if (a[ord.back()][j - 1] > a[ord[1]][j]) {
                std::cout << -1 << '\n';
                return ;
            }
        }

        for (int i = 1; i <= n; i += 1) {
            std::cout << ord[i] << " \n"[i == n];
        }
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
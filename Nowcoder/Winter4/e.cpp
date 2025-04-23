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
        }

        std::vector sufd(n + 1, std::vector<i64>(m + 1));
        std::vector sufu(n + 1, std::vector<i64>(m + 1));
        std::vector preu(n + 1, std::vector<i64>(m + 1));
        std::vector pred(n + 1, std::vector<i64>(m + 1));
        for (int i = n; i >= 1; i -= 1) {
            for (int j = m; j >= 1; j -= 1) {
                if (i + 1 <= n && j + 1 <= m) {
                    sufd[i][j] += sufd[i + 1][j + 1] + a[i + 1][j + 1];
                }
            }
        }

        for (int i = 1; i <= n; i += 1) {
            for (int j = m; j >= 1; j -= 1) {
                if (i - 1 >= 1 && j + 1 <= m) {
                    sufu[i][j] += sufu[i - 1][j + 1] + a[i - 1][j + 1];
                }
            }
        }

        for (int i = 1; i <= n; i += 1) {
            for (int j = 1; j <= m; j += 1) {
                if (i - 1 >= 1 && j - 1 >= 1) {
                    preu[i][j] += preu[i - 1][j - 1] + a[i - 1][j - 1];
                }
            }
        }

        for (int i = n; i >= 1; i -= 1) {
            for (int j = 1; j <= m; j += 1) {
                if (i + 1 <= n && j - 1 >= 1) {
                    pred[i][j] += pred[i + 1][j - 1] + a[i + 1][j - 1];
                }
            }
        }

        i64 res = 0;
        for (int i = 1; i <= n; i += 1) {
            for (int j = 1; j <= m; j += 1) {
                chmax(res, pred[i][j] + preu[i][j] + sufd[i][j] + sufu[i][j] + a[i][j]);
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
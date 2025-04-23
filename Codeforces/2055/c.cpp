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

        std::string s;
        std::cin >> s;

        std::vector a(n + 1, std::vector<i64>(m + 1));
        for (int i = 1; i <= n; i += 1) {
            for (int j = 1; j <= m; j += 1) {
                std::cin >> a[i][j];
            }
        }

        int l = s.size();
        std::vector<std::pair<int, int>>f(l + 2);
        f[1] = {1, 1};
        for (int i = 1, x = 1, y = 1; i <= l; i += 1) {
            if (s[i - 1] == 'D') {
                x += 1;
            } else {
                y += 1;
            }
            f[i + 1] = {x, y};
        }

        std::vector<i64>row(n + 1), col(m + 1);
        for (int i = 1; i <= n; i += 1) {
            row[i] = std::accumulate(a[i].begin(), a[i].end(), 0LL);
        }

        for (int j = 1; j <= m; j += 1) {
            for (int i = 1; i <= n; i += 1) {
                col[j] += a[i][j];
            }
        }

        debug(f);
        debug(row);
        debug(col);

        constexpr i64 inf = 100;

        {
            auto [r, c] = f[2];
            if (r == 2) {
                a[1][1] = -row[1];
            } else {
                a[1][1] = -col[1];
            }
            row[1] += a[1][1];
            col[1] += a[1][1];
        }

        for (int i = 2; i < f.size() - 1; i += 1) {
            auto [pr, pc] = f[i - 1];
            auto [r, c] = f[i];
            auto [nr, nc] = f[i + 1];
            if (r == pr + 1) {
                i64 cof = row[pr];
                if (nr == r + 1) {
                    a[r][c] = cof - row[r];
                } else {
                    a[r][c] = cof - col[c];
                }
                row[r] += a[r][c];
                col[c] += a[r][c];
            } else {
                i64 cof = col[pc];
                if (nc == c + 1) {
                    a[r][c] = cof - col[c];
                } else {
                    a[r][c] = cof - row[r];                    
                }
                row[r] += a[r][c];
                col[c] += a[r][c];
            }
        }

        a.back().back() = -row.back();

        for (int i = 1; i <= n; i += 1) {
            for (int j = 1; j <= m; j += 1) {
                std::cout << a[i][j] << " \n"[j == m];
            }
        }
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
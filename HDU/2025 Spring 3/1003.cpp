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

    std::vector<i64>a(m + 1);
    for (int i = 1; i <= m; i += 1) {
        std::cin >> a[i];
    }

    std::vector<std::vector<int>>c(n + 1, std::vector<int>(m + 1)), w(n + 1, std::vector<int>(m + 1));
    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= m; j += 1) {
            std::cin >> c[i][j];
        }
        for (int j = 1; j <= m; j += 1) {
            std::cin >> w[i][j];
        }
    }

    std::vector<std::vector<std::pair<int, int>>>q(m + 1, std::vector<std::pair<int, int>>());
    for (int k = 1; k <= m; k += 1) {
        for (int i = 1; i <= n; i += 1) {
            q[k].emplace_back(c[i][k], i);
        }
        std::sort(q[k].begin(), q[k].end(), std::greater());
    }

    int cnt = 0;
    std::vector<int>d(n + 1, m);
    while (true) {
        int pre = cnt;
        for (int k = 1; k <= m; k += 1) {
            while (!q[k].empty() && q[k].back().first <= a[k]) {
                if (--d[q[k].back().second] == 0) {
                    cnt += 1;
                    for (int j = 1; j <= m; j += 1) {
                        a[j] += w[q[k].back().second][j];
                    }
                }
                q[k].pop_back();
            }
        }
        if (pre == cnt) {
            break;
        }
    }

    std::cout << (cnt == n ? "YES\n" : "NO\n");
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
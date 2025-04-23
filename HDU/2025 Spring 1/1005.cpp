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

constexpr int dx[] = {0, 1, 0, -1};
constexpr int dy[] = {1, 0, -1, 0};

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto solve = [&]() {
        int n, m;
        std::cin >> n >> m;

        std::vector t(n + 1, std::vector(m + 1, 0)), d(n + 1, std::vector(m + 1, 0));
        for (int i = 1; i <= n; i += 1) {
            for (int j = 1; j <= m; j += 1) {
                std::cin >> t[i][j];
            }
        }

        for (int i = 1; i <= n; i += 1) {
            for (int j = 1; j <= m; j += 1) {
                std::cin >> d[i][j];
            }
        }

        constexpr i64 inf = 1E18;
        i64 res = inf;
        std::vector f(4, std::vector(n + 1, std::vector(m + 1, inf)));
        std::priority_queue<std::tuple<i64, int, int, int>, std::vector<std::tuple<i64, int, int, int>>, std::greater<>>q;
        f[0][1][1] = 0;
        q.push({0, 0, 1, 1});
        while (!q.empty()) {
            auto [h, k, x, y] = q.top();
            q.pop();
            if (h != f[k][x][y]) {
                continue;
            }
            for (int e = 0; e < 4; e += 1) {
                i64 w = 1LL * h + t[x][y] + (k == e ? 0LL : d[x][y]);
                if (x == n && y == m && e == 1) {
                    chmin(res, w);
                    continue;
                }
                int nx = x + dx[e], ny = y + dy[e];
                if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && chmin(f[e][nx][ny], w)) {
                    q.push({w, e, nx, ny});
                }
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
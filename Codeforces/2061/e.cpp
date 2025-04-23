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
        int n, m, k;
        std::cin >> n >> m >> k;
        
        std::vector<int>a(n + 1), b(m + 1);
        for (int i = 1; i <= n; i += 1) {
            std::cin >> a[i];
        }
        for (int i = 1; i <= m; i += 1) {
            std::cin >> b[i];
        }

        constexpr int inf = (1 << 30) - 1;
        std::vector<int>f(1 << m, inf);
        for (int s = 0; s < ( 1 << m); s += 1) {
            for (int i = 1; i <= m; i += 1) {
                if (s >> (i - 1) & 1) {
                    f[s] &= b[i];
                }
            }
        }

        std::vector g(n + 1, std::vector<int>(m + 1, inf));
        for (int i = 1; i <= n; i += 1) {
            for (int s = 0; s < (1 << m); s += 1) {
                chmin(g[i][__builtin_popcount(s)], a[i] & f[s]);
            }
        }

        std::vector<int>p(n + 1);
        std::priority_queue<std::pair<int, int>>q;
        for (int i = 1; i <= n; i += 1) {
            q.push({g[i][p[i]] - g[i][p[i] + 1], i});
        }

        i64 res = std::accumulate(a.begin() + 1, a.end(), 0LL);
        while (!q.empty() && k > 0) {
            auto [d, i] = q.top();
            q.pop();
            if (d <= 0) {
                break;
            }
            res -= d;
            p[i] += 1;
            k -= 1;
            if (p[i] <= m - 1) {
                q.push({g[i][p[i]] - g[i][p[i] + 1], i});
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
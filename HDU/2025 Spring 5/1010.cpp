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
    int n;
    std::cin >> n;

    std::vector adj(n + 1, std::vector<std::pair<int, int>>());
    for (int i = 1; i <= n - 1; i += 1) {
        int u, v, w;
        std::cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    std::vector<i64>d(n + 1);
    auto dfs = [&](auto && self, int u, int p) ->void {
        for (const auto & [v, w] : adj[u]) {
            if (v == p) {
                continue;
            }
            d[v] = d[u] + w;
            d[v] %= 2;
            self(self, v, u);
        }
    };
    dfs(dfs, 1, 0);

    int x = std::count(d.begin() + 1, d.end(), 0);
    int y = n - x;

    std::cout << (1LL * x * x * x + 1LL * y * y * y) << '\n';
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
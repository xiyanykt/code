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

        std::vector<int>deg(n + 1);
        std::vector<std::pair<int, int>>edges(n - 1);
        std::vector<std::vector<int>>adj(n + 1);
        for (auto & [u, v] : edges) {
            std::cin >> u >> v;
            deg[u] += 1;
            deg[v] += 1;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        if (n == 2) {
            std::cout << 0 << '\n';
            return ;   
        }

        int ans = 0;
        for (const auto & [u, v] : edges) {
            chmax(ans, deg[u] + deg[v] - 2);
        }

        std::multiset<int>s(deg.begin() + 1, deg.end());
        for (int u = 1; u <= n; u += 1) {
            s.extract(deg[u]);
            for (const auto & v : adj[u]) {
                s.extract(deg[v]);
                deg[v] -= 1;
                s.insert(deg[v]);
            }
            chmax(ans, deg[u] + (*s.rbegin()) - 1);
            s.insert(deg[u]);
            for (const auto & v : adj[u]) {
                s.extract(deg[v]);
                deg[v] += 1;
                s.insert(deg[v]);
            }
        }

        std::cout << ans << '\n';
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
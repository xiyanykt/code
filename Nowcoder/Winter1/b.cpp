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

    int n;
    std::cin >> n;

    std::vector<std::vector<int>>adj(n + 1);
    for (int i = 1; i <= n - 1; i += 1) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::vector<int>l;
    for (int u = 1; u <= n; u += 1) {
        if (adj[u].size() == 0 || adj[u].size() > 2) {
            std::cout << -1 << '\n';
            return 0;
        }
        if (adj[u].size() == 1) {
            l.push_back(u);
        }
    }

    if (l.size() <= 1) {
        std::cout << -1 << '\n';
    } else {
        std::cout << l[0] << ' ' << l.back() << '\n';
    }

    return 0;
}
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

    bool ok = true;
    std::vector<int>deg(3 * n + 1);
    std::vector<std::vector<int>>adj(3 * n + 1);
    for (int i = 1; i <= m; i += 1) {
        int x, y, c;
        std::cin >> x >> y >> c;

        int u = 2 * n - x + 1;
        int v = (y + 1) / 2;
        int w = 2 * n + x - y / 2;
        if (u == c) {
            adj[v].push_back(u);
            adj[w].push_back(u);
            deg[u] += 2;
        } else if (v == c) {
            adj[u].push_back(v);
            adj[w].push_back(v);
            deg[v] += 2;
        } else if (w == c) {
            adj[u].push_back(w);
            adj[v].push_back(w);
            deg[w] += 2;
        } else {
            ok = false;
        }
    }

    if (!ok) {
        std::cout << "No\n";
        return ;
    }

    std::queue<int>q;
    for (int u = 1; u <= 3 * n; u += 1) {
        if (deg[u] == 0) {
            q.push(u);
        }
    }

    int cnt = 0;
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        cnt += 1;
        for (const auto & v : adj[u]) {
            if (--deg[v] == 0) {
                q.push(v);
            }
        }
    }

    std::cout << (cnt == 3 * n ? "Yes\n" : "No\n");
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
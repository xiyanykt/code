#include<bits/stdc++.h>

using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128;
using f128 = __float128;

#ifndef ONLINE_JUDGE
#include "algo\debug.hpp"
#else
#define debug(...) (void)42
#endif

template<class T>
void chmax(T& x, T y) {
    x = std::max(x, y);
}

template<class T>
void chmin(T& x, T y) {
    x = std::min(x, y);
}

auto main() ->int32_t {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::fixed << std::setprecision(13);

    int n, q, s;
    std::cin >> n >> q >> s;

    const int delta = 4 * n;
    std::vector adj(2 * delta + 1, std::vector<std::pair<int, int>>());
    std::vector<int>Index(n + 1);

    auto addEdge = [&](int u, int v, int w) {
        adj[u].emplace_back(v, w);
    };

    auto build = [&](this auto && self, int p, int l, int r) {
        if (l == r) {
            Index[l] = p;
            addEdge(p, p + delta, 0);
            return ;
        }
        int mid = (l + r) / 2, lsh = 2 * p, rsh = 2 * p + 1;
        addEdge(p, lsh, 0);
        addEdge(p, rsh, 0);
        addEdge(lsh + delta, p + delta, 0);
        addEdge(rsh + delta, p + delta, 0);
        self(lsh, l, mid);
        self(rsh, mid + 1, r);
    };

    auto update = [&](this auto && self, int p, int l, int r, int v, int L, int R, int w, int o) {
        if (L <= l and r <= R) {
            if (o == 2) {
                addEdge(Index[v] + delta, p, w);
            } else {
                addEdge(p + delta, Index[v], w);
            }
            return;
        }
        int mid = (l + r) / 2;
        if (L <= mid) {
            self(p << 1, l, mid, v, L, R, w, o);
        }
        if (mid < R) {
            self(p << 1 | 1, mid + 1, r, v, L, R, w, o);
        }
    };

    build(1, 1, n);

    while (q--) {
        int o;
        std::cin >> o;
        if (o == 1) {
            int v, u, w;
            std::cin >> v >> u >> w;
            addEdge(Index[v] + delta, Index[u], w);
        } else {
            int v, l, r, w;
            std::cin >> v >> l >> r >> w;
            update(1, 1, n, v, l, r, w, o);
        }
    }

    std::priority_queue<std::pair<i64, int>, std::vector<std::pair<i64, int>>, std::greater<>>Q;
    std::vector<i64>dis(2 * delta + 1, -1);
    Q.emplace(dis[Index[s]] = 0, Index[s]);
    while (not Q.empty()) {
        auto [d, u] = Q.top();
        Q.pop();
        if (d != dis[u]) {
            continue;
        }
        for (const auto & [v, w] : adj[u]) {
            if (dis[v] == -1 or dis[v] > dis[u] + w) {
                Q.emplace(dis[v] = dis[u] + w, v);
            }
        }
    }

    for (int i = 1; i <= n; i += 1) {
        std::cout << dis[Index[i]] << ' ';
    }

    return 0;
}
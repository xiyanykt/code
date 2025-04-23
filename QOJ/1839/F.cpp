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

struct SCC {
    int n;
    std::vector<std::vector<int>>adj;
    std::vector<int>low, bel, dfn, stk;
    int cnt, cur;
    SCC() = default;
    SCC(int n): n{n}, adj(n + 1), low(n + 1), bel(n + 1, -1), dfn(n + 1, -1), stk{}, cnt{0}, cur{0} {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void tarjan(int u) {
        dfn[u] = low[u] = ++cur;
        stk.emplace_back(u);

        for (const auto & v : adj[u]) {
            if (dfn[v] == -1) {
                tarjan(v);
                low[u] = std::min(low[u], low[v]);
            } else if (bel[v] == -1) {
                low[u] = std::min(low[u], dfn[v]);
            }
        }
        if (low[u] == dfn[u]) {
            int v;
            cnt += 1;
            do {
                v = stk.back();
                stk.pop_back();
                bel[v] = cnt;
            } while (v != u);
        }
    }

    auto work() {
        for (int u = 1; u <= n; u += 1) {
            if (dfn[u] == -1) {
                tarjan(u);
            }
        }
        return bel;
    }
};

void solve () {
    int n, k, q;
    std::cin >> n >> k >> q;
        
    SCC scc(n);
    std::vector<std::vector<int>>a(k + 1, std::vector<int>(n + 1));
    for (int i = 1; i <= k; i += 1) {
        for (int j = 1; j <= n; j += 1) {
            std::cin >> a[i][j];
            if (j >= 2) {
                scc.addEdge(a[i][j - 1], a[i][j]);
            }
        }
    }
    
    auto v = scc.work();
    std::vector pre(k + 1, std::vector<int>(n + 1)), suf(k + 1, std::vector<int>(n + 1));
    std::vector sum(k + 1, std::vector<i64>(n + 1));
    for (int i = 1; i <= k; i += 1) {
        suf[i].back() = n;
        pre[i][1] = 1;
        for (int j = n - 1; j >= 1; j -= 1) {
            suf[i][j] = (v[a[i][j]] == v[a[i][j + 1]] ? suf[i][j + 1] : j);
        }
        for (int j = 2; j <= n; j += 1) {
            pre[i][j] = (v[a[i][j]] == v[a[i][j - 1]] ? pre[i][j - 1] : j);
        }
        for (int j = 1; j <= n; j = suf[i][j] + 1) {
            int len = (suf[i][j] - j + 1);
            if (suf[i][j] + 1 <= n) {
                sum[i][suf[i][j] + 1] += 1LL * len * (len - 1) / 2;
            }
        }
        for (int j = 1; j <= n; j += 1) {
            sum[i][j] += sum[i][j - 1];
        }
    }
    i64 ans = 0;
    for (int t = 1; t <= q; t += 1) {
        i64 i, l, r;
        std::cin >> i >> l >> r;
        i = (i + ans) % k + 1;
        l = (l + ans) % n + 1;
        r = (r + ans) % n + 1;
    
        int lo = suf[i][l], hi = pre[i][r];
        if (lo < hi) {
            std::cout << (ans = (1LL * (lo - l + 1) * (lo - l) / 2 + 1LL * (r - hi + 1) * (r - hi) / 2 + sum[i][hi] - sum[i][lo + 1])) << '\n';
        } else {
            std::cout << (ans = 1LL * (r - l + 1) * (r - l) / 2) << '\n';
        }
    }
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

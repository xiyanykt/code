#include<bits/stdc++.h>
using i64 = long long;

auto main() ->int32_t {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, x;
    std::cin >> n >> m >> x;

    std::vector<int>a(n + 1);
    for (int i = 1; i <= n; i += 1) {
        std::cin >> a[i];
    }

    std::vector adj(n + 1, std::vector<std::array<int, 2>>());
    for (int i = 1; i <= m; i += 1) {
        int u, v, w;
        std::cin >> u >> v >> w;
        if (u > v) {
            std::swap(u, v);
        }
        adj[u].push_back({v, w});
    }

    constexpr i64 inf = 1E18;
    std::vector<i64>dp(n + 1, -inf);
    dp[1] = x + a[1];
    for (int u = 1; u <= n; u += 1) {
        if (dp[u] == -inf) {
            continue;
        }
        for (const auto & [v, w] : adj[u]) {
            if (v > u && dp[v] < dp[u] + a[v] - w) {
                dp[v] = dp[u] + a[v] - w;
            }
        }
    }

    if (dp.back() == -inf) {
        std::cout << "NO\n";
        return 0;
    }

    std::cout << dp.back() << '\n';
    return 0;
}
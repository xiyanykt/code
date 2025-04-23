#include<bits/stdc++.h>

using i64 = long long;

auto main() ->int32_t {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;

    std::vector adj(n + 1, std::vector<std::array<int, 2>>());
    for (int i = 1; i <= n - 1; i += 1) {
        int u, v, w;
        std::cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    std::vector<int>s(n + 1);
    auto dfs = [&](auto && dfs, int u, int par) ->void {
        for (const auto & [v, w] : adj[u]) {
            if (v == par) {
                continue;
            }
            s[v] = s[u] ^ w;
            dfs(dfs, v, u);
        }
    };
    dfs(dfs, 1, 0);

    constexpr int Kn = 30;
    std::vector<std::array<int, Kn>>f(n + 1);
    for (int u = 1; u <= n; u += 1) {
        for (int j = 0; j < Kn; j += 1) {
            f[u][j] = f[u - 1][j] + (s[u] >> j & 1);
        }
    }

    int q;
    std::cin >> q;
    while (q--) {
        int l, r, x;
        std::cin >> l >> r >> x;
        i64 t = 0;

        for (int j = 0; j < Kn; j += 1) {
            if (~s[x] >> j & 1) {
                t += (1LL << j) * (f[r][j] - f[l - 1][j]);
            } else {
                t += (1LL << j) * (r - l + 1 - (f[r][j] - f[l - 1][j]));
            }
        }

        std::cout << t << '\n';
    }
    return 0;
}
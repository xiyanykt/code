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

constexpr int Mod = 1E9 + 7;

int add (int a, int b) {
    int c = (a + b);
    if (c >= Mod) {
        c -= Mod;
    }
    return c;
}

int mul (int a, int b) {
    return i64(a) * b % Mod;
}

int power (int a, int b) {
    int r = 1;
    for (; b != 0; b >>= 1, a = mul(a, a)) {
        if (b & 1) {
            r = mul(r, a);
        }
    }
    return r;
}

constexpr int Kn = 1E5;
constexpr int Kw = 30;
i64 g[Kn + 1];
i64 d[Kn + 1];
i64 f[2][Kn + 1][Kw];

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int>a(n + 1);
    for (int i = 1; i <= n; i += 1) {
        std::cin >> a[i];
    }

    std::vector<std::vector<int>>adj(n + 1);
    for (int i = 1; i <= n - 1; i += 1) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int res = 0;
    auto dfs = [&](auto && dfs, int u, int p) ->void {
        for (int k = 0; k < Kw; k += 1) {
            if (a[u] >> k & 1) {
                f[1][u][k] = 1;
            } else {
                f[0][u][k] = 1;
            }
        }
        g[u] = 1;
        for (const auto & v : adj[u]) {
            if (v == p) {
                continue;
            }
            dfs(dfs, v, u);
            d[u] = (d[u] + d[u] * g[v] % Mod + d[v] * g[u] % Mod) % Mod;
            for (int k = 0; k < Kw; k += 1) {
                d[u] = (d[u] + 
                    (1 << k) * f[0][u][k] % Mod * f[1][v][k] % Mod +
                    (1 << k) * f[1][u][k] % Mod * f[0][v][k] % Mod
                ) % Mod;
                f[0][u][k] = (f[0][u][k] + 
                    f[0][u][k] * g[v] % Mod +
                    f[0][v][k] * g[u] % Mod
                ) % Mod;
                f[1][u][k] = (f[1][u][k] + 
                    f[1][u][k] * g[v] % Mod +
                    f[1][v][k] * g[u] % Mod
                ) % Mod;
            }
            g[u] = (g[u] + g[u] * g[v] % Mod) % Mod;
        }
    };
    dfs(dfs, 1, 0);

    for (int u = 1; u <= n; u += 1) {
        res = add(res, d[u]);
    }

    std::cout << mul(res, 2) << '\n';

    return 0;
}
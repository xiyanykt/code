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

struct Info {
    int b = 0;
    int w = 0;
    i64 sb = 0;
    i64 sw = 0;
    i64 s = 0;

    constexpr friend Info operator+(Info a, const Info& b) {
        a.s += b.s;
        a.s += a.sw * b.b + a.w * (b.sb + b.b);
        a.s += a.sb * b.w + a.b * (b.sw + b.w);
        a.sb += b.sb + b.b;
        a.sw += b.sw + b.w;
        a.b += b.b;
        a.w += b.w;
        return a;
    }

    constexpr friend Info operator-(Info a, const Info& b) {
        a.b -= b.b;
        a.w -= b.w;
        a.sb -= b.sb + b.b;
        a.sw -= b.sw + b.w;
        a.s -= a.sb * b.w + a.b * (b.sw + b.w);
        a.s -= a.sw * b.b + a.w * (b.sb + b.b);
        a.s -= b.s;
        return a;
    }
};

struct customHash {
    static unsigned long long salt(unsigned long long x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(const std::pair<u64, u64>& x) const {
        static const unsigned long long r = std::chrono::steady_clock::now().time_since_epoch().count();
        return salt(salt(x.first + r) + salt(x.second + r) + r);
    }
};

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;
    s = ' ' + s;

    std::unordered_map<std::pair<unsigned long long, unsigned long long>, std::pair<i64, i64>, customHash>r;
    std::vector<std::pair<int, int>>edges;
    std::vector<std::vector<int>>adj(n + 1);
    for (int i = 1; i <= n - 1; i += 1) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        r[{u, v}] = {};
        edges.push_back({u, v});
    }

    std::vector<Info>f(n + 1);
    std::vector<i64>x(n + 1), y(n + 1);
    auto dfs = [&](auto && dfs, int u, int p) ->void {
        (s[u] == 'b' ? f[u].b : f[u].w) += 1;
        for (const auto & v : adj[u]) {
            if (v == p) {
                continue;
            }
            dfs(dfs, v, u);
            f[u] = f[u] + f[v];
        }
    };
    dfs(dfs, 1, 0);

    auto work = [&](auto&& work, int u, int p) ->void {
        for (const auto & v : adj[u]) {
            if (v == p) {
                continue;
            }
            f[u] = f[u] - f[v];
            if (r.contains({u, v})) {
                r[{u, v}] = {f[u].s, f[v].s};
            } 
            if (r.contains({v, u})) {
                r[{v, u}] = {f[v].s, f[u].s};
            }
            f[v] = f[v] + f[u];
            work(work, v, u);
            f[v] = f[v] - f[u];
            f[u] = f[u] + f[v];
        }
    };
    work(work, 1, 0);

    for (const auto & [u, v] : edges) {
        auto [x, y] = r[{u, v}];
        std::cout << x << ' ' << y << '\n';
    }
    return 0;
}
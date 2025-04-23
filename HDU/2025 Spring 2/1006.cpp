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
    constexpr int W = 5;
    int sg[W][W][W];
    auto dfs = [&](auto && dfs, int r, int b, int m, int o) {
        if (sg[r][b][m] != -1) {
            return sg[r][b][m];
        }
        std::set<int>h;
        if (r >= 1) {
            h.insert(dfs(dfs, r - 1, b, m, o ^ 1));
        }
        if (r >= 2) {
            h.insert(dfs(dfs, r - 2, b, m, o ^ 1));
        }
        if (r >= 3) {
            h.insert(dfs(dfs, r - 3, b, m, o ^ 1));
        }
        if (b >= 1) {
            h.insert(dfs(dfs, r + 1, b - 1, m, o ^ 1));
        }
        if (b >= 1) {
            h.insert(dfs(dfs, r, b - 1, m, o ^ 1));
            if (r >= 1) {
                h.insert(dfs(dfs, r - 1, b - 1, m, o ^ 1));
            }
        }
        if (b >= 2) {
            h.insert(dfs(dfs, r + 1, b - 2, m, o ^ 1));
        }
        if (m >= 1) {
            h.insert(dfs(dfs, r + 1, b, m - 1, o ^ 1));
            h.insert(dfs(dfs, r, b + 1, m - 1, o ^ 1));
            h.insert(dfs(dfs, r + 1, b + 1, m - 1, o ^ 1));
        }
        sg[r][b][m] = 0;
        while (h.contains(sg[r][b][m])) {
            sg[r][b][m] += 1;
        }
        return sg[r][b][m];
    };
    memset(sg, -1, sizeof(sg));
    for (int r = 0; r <= 3; r += 1) {
        for (int b = 0; b <= 3; b += 1) {
            for (int m = 0; m <= 3; m += 1) {
                std::cout << std::format("r = {}, b = {}, m = {}, (r + 2b + 4m) % 4 = {}, sg = {}\n", r, b, m, (r + 2 * b + 4 * m) % 4,dfs(dfs, r, b, m, 0));
            }
        }
    }
}

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t = 1;
    std::cin >> t;
    while (t--) {
        // solve();
        int r, b, m;
        std::cin >> r >> b >> m;

        std::cout << ((1LL * r + 2LL * b + 4LL * m) % 4 == 0 ? "Bob\n" : "Alice\n");
    }
    return 0;
}
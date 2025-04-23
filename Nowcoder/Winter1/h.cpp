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

    std::vector<int>l(n + 1), r(n + 1);
    for (int i = 1; i <= n; i += 1) {
        std::cin >> l[i] >> r[i];
    }

    std::vector<int>res(n + 1);
    std::vector<std::vector<int>>adj(n + 1);
    for (int i = 1; i <= n; i += 1) {
        adj[l[i]].push_back(i);
    }

    std::priority_queue<std::array<int, 2>, std::vector<std::array<int, 2>>, std::greater<>>q;
    for (int l = 1; l <= n; l += 1) {
        for (const auto & i : adj[l]) {
            q.push({r[i], i});
        }
        if (q.empty()) {
            std::cout << -1 << '\n';
            return 0;
        }
        auto [r, i] = q.top();
        q.pop();
        if (l > r) {
            std::cout << -1 << '\n';
            return 0;
        }
        res[i] = l;
    }

    for (int i = 1; i <= n; i += 1) {
        std::cout << res[i] << " \n"[i == n];
    }
    return 0;
}
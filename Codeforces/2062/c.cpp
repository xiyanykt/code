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

    auto solve = [&]() {
        int n;
        std::cin >> n;

        std::vector<int>a(n);
        for (int i = 0; i < n; i += 1) {
            std::cin >> a[i];
        }

        int s = std::accumulate(a.begin(), a.end(), 0);
        auto dfs = [&](this auto && dfs, std::vector<int> a) {
            debug(a);
            if (a.size() == 1) {
                chmax(s, a[0]);
                return ;
            }
            chmax(s, std::accumulate(a.begin(), a.end(), 0));
            std::vector<int>b;
            for (int i = 1; i < a.size(); i += 1) {
                b.push_back(a[i] - a[i - 1]);
            }
            dfs(b);
            std::ranges::reverse(a);
            b.clear();
            for (int i = 1; i < a.size(); i += 1) {
                b.push_back(a[i] - a[i - 1]);
            }
            dfs(b);
        };
        dfs(a);
        std::ranges::reverse(a);
        dfs(a);

        std::cout << s << '\n';
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
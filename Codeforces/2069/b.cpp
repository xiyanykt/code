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

constexpr int dx[] = {-1, 1, 0, 0};
constexpr int dy[] = {0, 0, 1, -1};

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto solve = [&]() {
        int n, m;
        std::cin >> n >> m;

        std::set<int>s;
        std::vector c(n + 1, std::vector<int>(m + 1));
        for (int i = 1; i <= n; i += 1) {
            for (int j = 1; j <= m; j += 1) {
                std::cin >> c[i][j];
                s.insert(c[i][j]);
            }
        }

        if (s.size() == 1) {
            std::cout << 0 << '\n';
            return ;
        }

        
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
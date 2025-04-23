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
        int n, m;
        std::cin >> n >> m;

        std::priority_queue<int>a, b;
        for (int i = 1; i <= n; i += 1) {
            int x;
            std::cin >> x;
            a.push(x);
        }        

        for (int i = 1; i <= m; i += 1) {
            int x;
            std::cin >> x;
            b.push(x);
        }

        while (!a.empty()) {
            if (b.empty() || b.size() > a.size()) {
                std::cout << "NO\n";
                return ;
            }
            int x = b.top();
            b.pop();
            if (x < a.top()) {
                std::cout << "NO\n";
                return ;
            }
            if (x == a.top()) {
                a.pop();
            } else {
                b.push(x / 2);
                b.push((x + 1) / 2);
            }
        }

        if (b.empty()) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
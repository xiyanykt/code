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

        std::vector a(n + 1, std::vector<int>(n + 1));
        for (int i = 1; i <= n; i += 1) {
            std::string s;
            std::cin >> s;
            for (int j = 1; j <= n; j += 1) {
                a[i][j] = s[j - 1] - '0';
            }
        }

        if (n == 1) {
            std::cout << 1 << '\n';
            return ;
        }

        std::vector<int>deg(n + 1);
        std::vector<std::vector<int>>adj(n + 1);
        for (int i = 1; i <= n; i += 1) {
            for (int j = i + 1; j <= n; j += 1) {
                if (a[i][j]) {
                    deg[j] += 1;
                    adj[i].push_back(j);
                }
            }
        }

        std::priority_queue<int>q;
        for (int u = 1; u <= n; u += 1) {
            if (deg[u] == 0) {
                q.push(u);
            }
        }

        while (!q.empty()) {
            auto u =q.top();
            q.pop();
            std::cout << u << ' ';
            for (const auto & v : adj[u]) {
                if (--deg[v] == 0){
                    q.push(v);
                }
            }
        }

        std::cout << '\n';
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
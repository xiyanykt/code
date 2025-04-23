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
        int n, p, k;
        std::cin >> n >> p >> k;

        std::vector<int>a(n + 1);
        for (int i = 1; i <= n; i += 1) {
            std::cin >> a[i];
            a[i] %= p;
        }

        std::sort(a.begin() + 1, a.end());
        std::priority_queue<std::array<int, 4>>q;
        for (int i = 2; i <= n; i += 1) {
            int j = std::lower_bound(a.begin() + 1, a.begin() + i, p - a[i]) - a.begin();
            if (j < i) {
                q.push({(a[i - 1] + a[i]) % p, i - 1, i, j});
            }
            if (j > 1) {
                q.push({(a[j - 1] + a[i]) % p, j - 1, i, 1});
            }
        }

        for (int i = 1; i <= k; i += 1) {
            if (!q.empty()) {
                auto [f, l, r, h] = q.top();
                q.pop();
                std::cout << f << ' ';
                if (l != h) {
                    l -= 1;
                    q.push({(a[l] + a[r]) % p, l, r, h});
                }
            } else {
                std::cout << -1 << ' ';
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
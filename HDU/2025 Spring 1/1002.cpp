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

constexpr int P = 998244353;

constexpr int power(int a, int b, int r = 1) {
    for (; b != 0; b >>= 1, a = 1LL * a * a % P) {
        if (b & 1) {
            r = 1LL * r * a % P;
        }
    }
    return r;
}

constexpr int inv(int x) {
    return power(x, P - 2);
}

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto solve = [&]() {
        int n, k, p;
        std::cin >> n >> k >> p;
        p -= 1;
        n -= 1;

        std::vector<std::pair<int, int>>f(k);
        for (auto & [p, v] : f) {
            std::cin >> p;
            p -= 1;
        }

        int res = 1;
        std::sort(f.begin(), f.end());
        for (int k = 0; k < 30; k += 1) {
            std::vector<std::pair<int, int>>g;
            for (auto [k, v] : f) {
                if (k == n && k % 2 == 0) {
                    g.push_back({k >> 1, v});
                } else if ((p >> 1) == (k >> 1)) {
                    res = 1LL * res * v % P;
                } else {
                    if (!g.empty() && g.back().first == (k >> 1)) {
                        g.back().second = (1LL * g.back().second + 1LL * (v - 1) * inv(2) % P + P) % P;
                    } else {
                        g.push_back({k >> 1, 1LL * (v + 1) * inv(2) % P});
                    }
                }
            }
            std::swap(g, f);
            p >>= 1;
            n >>= 1;
        }

        std::cout << res << '\n';
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
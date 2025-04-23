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

        std::unordered_map<int, int>r;
        for (int i = 1; i <= n; i += 1) {
            std::vector<int>p(3);
            std::cin >> p[0] >> p[1] >> p[2];

            std::vector<int>t;
            std::sort(p.begin(), p.end());
            do {
                int a = p[0], b = p[1], c = p[2];
                if ((c - b) % a == 0) {
                    t.push_back((c - b) / a);
                }
            } while (std::next_permutation(p.begin(), p.end()));
            std::sort(t.begin(), t.end());
            t.erase(std::unique(t.begin(), t.end()), t.end());
            for (const auto & h : t) {
                r[h] += 1;
            }
        }

        for (const auto & [x, f] : r) {
            if (f == n) {
                std::cout << x << '\n';
                return ;
            }
        }
        assert(false);
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
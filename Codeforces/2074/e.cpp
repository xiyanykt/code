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

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int rand(int l, int r) {
    return std::uniform_int_distribution<int>(l, r)(rng);
}

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto solve = [&]() {
        int n;
        std::cin >> n;

        auto ask = [&](int i, int j, int k) {
            std::cout << std::format("? {} {} {}", i, j, k) << std::endl;
            int h;
            std::cin >> h;
            assert(h != -1);
            return h;
        };

        auto ans = [&](int i, int j, int k) {
            std::cout << std::format("! {} {} {}", i, j, k) << std::endl;
        };

        std::queue<std::array<int, 3>>q;
        q.push({1, 2, 3});
        for (int t = 0; t < 75 && !q.empty(); t += 1) {
            auto [i, j, k] = q.front();
            q.pop();
            int h = ask(i, j, k);
            if (h == 0) {
                ans(i, j, k);
                return ;
            }
            int e = ask(i, j, h);
            if (e == 0) {
                ans(i, j, h);
                return ;
            } else {
                q.push({i, j, h});
            }
            e = ask(i, h, k);
            if (e == 0) {
                ans(i, h, k);
                return ;
            } else {
                q.push({i, h, k});
            }
            e = ask(h, j, k);
            if (e == 0) {
                ans(h, j, k);
                return ;
            } else {
                q.push({h, j, k});
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
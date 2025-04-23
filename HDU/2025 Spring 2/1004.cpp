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

constexpr int W = 26;

void solve () {
    f64 k;
    std::string s;
    std::cin >> s >> k;

    auto t = s;
    if (k >= 2 * W) {
        for (int i = 1; i <= 2 * W; i += 1) {
            s += t;
        }
    } else {
        for (int i = 1; i <= int(k - 1); i += 1) {
            s += t;
        }
    }

    int n = s.size();
    s = ' ' + s;
    std::array<int, W>g{};
    std::vector<int>f(n + 1);
    for (int i = 1; i <= n; i += 1) {
        int x = 0;
        for (int k = 0; k < (s[i] - 'a'); k += 1) {
            chmax(x, g[k]);
        }
        f[i] = x + 1;
        chmax(g[s[i] - 'a'], f[i]);
    }

    std::cout << *std::max_element(f.begin(), f.end()) << '\n';
}

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
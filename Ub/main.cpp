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

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, k;
    std::cin >> n >> k;

    i64 sum = 0;
    std::vector<int>p(n + 1), s(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> p[i] >> s[i];
        sum += p[i];
        sum += s[i];
    }

    i64 ans = 1E18;
    for (int i = 1; i <= n; i += 1) {

    }
    return 0;
}
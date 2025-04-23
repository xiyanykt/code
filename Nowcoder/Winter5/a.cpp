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

    i64 x;
    char o;
    std::cin >> x >> o;

    if (o == '+') {
        std::cout << 1 << ' ' << x - 1 << '\n';
    } else if (o == '-') {
        std::cout << x + 1 << ' ' << 1 << '\n';
    } else if (o == '*') {
        std::cout << 1 << ' ' << x << '\n';
    } else {
        assert(false);
    }

    return 0;
}
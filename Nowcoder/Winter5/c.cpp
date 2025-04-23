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

    int n, x, y;
    std::cin >> n >> x >> y;

    std::vector<int>a(n + 1), b(n + 1), c(n + 1);
    {
        std::string s;
        std::cin >> s;
        for (int i = 0; i < n; i += 1) {
            a[i + 1] = s[i] - '0';
        }
    }
    {
        std::string s;
        std::cin >> s;
        for (int i = 0; i < n; i += 1) {
            b[i + 1] = s[i] - '0';
        }
    }
    {
        std::string s;
        std::cin >> s;
        for (int i = 0; i < n; i += 1) {
            c[i + 1] = s[i] - '0';
        }
    }

    i64 res = 0;
    std::map<std::pair<int, int>, int>r;
    for (int i = 1; i <= n; i += 1) {
        if ((a[i] ^ b[i]) == c[i]) {
            continue;
        }
        res += x;
        r[{a[i], b[i]}] += 1;
    }

    int cnt = r[{0, 1}] + r[{1, 0}] + r[{0, 0}] + r[{1, 1}];
    int max = std::max({r[{0, 1}], r[{1, 0}], r[{0, 0}], r[{1, 1}]});
    if (max >= cnt - max) {
        chmin(res, 1LL * y * (cnt - max) + 1LL * x * (2 * max - cnt));
    } else {
        chmin(res, 1LL * (cnt / 2) * y + 1LL * x * (cnt % 2));
    }
    std::cout << res << '\n';
    return 0;
}
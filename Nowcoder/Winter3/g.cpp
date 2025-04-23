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

    int n, k;
    std::cin >> n >> k;

    auto f = [&](int x) {
        int cnt = 0;
        i64 sum = 0;
        for (int l = 1, r = 1; l <= n; l = r + 1) {
            r = n / (n / l);
            int i = std::min(r, (n - x) / (n / l));
            if (i >= l) {
                cnt += i - l + 1;
                sum += 1LL * (i - l + 1) * (n - 1LL * l * (n / l) + n - 1LL * i * (n / l)) / 2;
            }
        }
        return std::pair(cnt, sum);
    };

    int lo = 0, hi = n;
    while (lo <= hi) {
        int mid = (lo + hi) >> 1;
        if (f(mid).first <= k) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    auto [cnt, sum] = f(hi + 1);
    std::cout << (sum + 1LL * (k - cnt) * (hi)) << '\n';
    return 0;
}
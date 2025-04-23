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

        std::vector<int>a(n + 1);
        for (int i = 1; i <= n; i += 1) {
            std::cin >> a[i];
        }

        i64 res = 0;
        std::map<int, int>rec;
        for (int l = 1, r = 1; l <= n;) {
            while (r <= n && (rec.contains(a[r]) || rec.size() <= 1)) {
                rec[a[r]] += 1;
                r += 1;
            }
            if (rec.size() != 2) {
                break;
            }
            std::vector<int>b;
            for (int i = l; i < r; i += 1) {
                b.push_back(a[i] == a[l] ? 1 : -1);
            }
            int sum = 0;
            std::map<int, int>f;
            f[0] += 1;
            for (const auto & c : b) {
                sum += c;
                res += f[sum]++;
            }
            while (l <= n && rec.size() == 2) {
                if (--rec[a[l]] == 0) {
                    rec.erase(a[l]);
                }
                l += 1;
            }
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
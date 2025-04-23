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

    int n;
    std::string s;
    std::cin >> n >> s;

    s = ' ' + s;

    if (n <= 2) {
        std::cout << 0 << '\n';
        return 0;
    }

    auto work = [&]() {
        std::vector<std::array<int, 26>>cnt(n + 1);
        for (int i = n; i >= 1; i -= 1) {
            cnt[i][s[i] - 'a'] += 1;
            if (i < n) {
                for (int k = 0; k < 26; k += 1) {
                    cnt[i][k] += cnt[i + 1][k];
                }
            }
        }

        int r = 1;
        while (r <= n) {
            bool ok = false;
            for (int k = 0; k < 26; k += 1) {
                if (cnt[r][k] >= 2) {
                    ok = true;
                }
            }
            if (ok) {
                r += 1;
            } else {
                break;
            }
        }
        return r - 1;
    };

    int r = work();
    std::reverse(s.begin() + 1, s.end());
    r = std::max(r, work());

    std::cout << r << '\n';
    return 0;
}
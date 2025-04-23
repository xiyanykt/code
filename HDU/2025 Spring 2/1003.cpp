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

void solve () {
    int n;
    std::cin >> n;

    std::vector<int>a(n + 1);
    for (int i = 1; i <= n; i += 1) {
        std::cin >> a[i];
    }

    int x = *std::max_element(a.begin() + 1, a.end());
    std::vector<std::vector<int>>c(x + 1);
    for (int i = 1; i <= n; i += 1) {
        c[a[i]].push_back(i);
    }

    std::vector<std::vector<int>>query(n + 1);
    for (int p = 1; p <= x; p += 1) {
        if (c[p].size() <= 1) {
            continue;
        }
        auto it = std::lower_bound(c[0].begin(), c[0].end(), c[p][0]);
        if (it != c[0].end()) {
            auto h = std::lower_bound(c[p].begin(), c[p].end(), *it);
            if (h != c[p].end()) {
                query[*h].push_back(p);
            }
        }
    }

    i64 ans = 0;
    int cnt = 0;
    std::vector<int>ocr(x + 1);
    for (int i = n; i >= 1; i -= 1) {
        ans += 1LL * query[i].size() * cnt;
        if (!ocr[a[i]] && a[i]) {
            cnt += 1;
        }
        ocr[a[i]] += 1;
    }

    std::cout << ans << '\n';
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
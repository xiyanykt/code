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
        int n, k;
        std::cin >> n >> k;

        std::string s;
        std::cin >> s;
        s = ' ' + s;

        std::vector<int>a(n + 1);
        for (int i = 1; i <= n; i += 1) {
            std::cin >> a[i];
        }

        auto work = [&](int x) {
            std::vector<int>p;
            for (int i = 1; i <= n; i += 1) {
                if (a[i] > x && s[i] == 'B') {
                    p.push_back(i);
                }
            }

            if (p.empty()) {
                return true;
            }

            int l = -1;
            std::vector<std::pair<int, int>>g;
            for (int i = 1; i <= n; i += 1) {
                if ((s[i] == 'R' && a[i] <= x) || (s[i] == 'B')) {
                    if (l == -1) {
                        l = i;
                    }
                } else {
                    if (l != -1) {
                        g.push_back({l, i - 1});
                        l = -1;
                    }
                }
            }
            if (l != -1) {
                g.push_back({l, n});
            }

            int w = 0;
            std::set<int>q;
            for (const auto & [l, r] : g) {
                auto v = std::ranges::lower_bound(p, l);
                if (v != p.end() && *v <= r) {
                    q.insert(int(v - p.begin()));
                }
            }
            return int(q.size()) <= k;
        };

        int lo = 0, hi = 1E9;
        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
            if (work(mid)) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        hi += 1;

        std::cout << hi << '\n';
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
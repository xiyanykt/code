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

        std::string s;
        std::cin >> s;

        constexpr int K = 26;
        std::array<int, K>cnt {};
        for (auto& c : s) {
            cnt[c - 'A'] += 1;
        }

        cnt['C' - 'A'] -= 2;
        cnt['H' - 'A'] -= 1;
        cnt['I' - 'A'] -= 1;
        cnt['K' - 'A'] -= 1;
        cnt['E' - 'A'] -= 1;
        cnt['N' - 'A'] -= 1;
        for (int k = 0; k < K; k += 1) {
            if (cnt[k] < 0) {
                std::cout << "NO\n";
                return ;
            }
        }

        if (std::accumulate(cnt.begin(), cnt.end(), 0) % 2 == 0 && std::ranges::max(cnt) <= std::accumulate(cnt.begin(), cnt.end(), 0) / 2) {
            auto find = [&](char c, int i) ->int {
                for (int j = i + 1; j < n; j += 1) {
                    if (s[j] == c) {
                        return j;
                    }
                }
                return -1;
            };

            int i = find('C', -1);
            if (i == -1) {
                std::cout << "NO\n";
                return ;
            }

            i = find('H', i);
            if (i == -1) {
                std::cout << "NO\n";
                return ;
            }

            i = find('I', i);
            if (i == -1) {
                std::cout << "NO\n";
                return ;
            }

            i = find('C', i);
            if (i == -1) {
                std::cout << "NO\n";
                return ;
            }

            i = find('K', i);
            if (i == -1) {
                std::cout << "NO\n";
                return ;
            }

            i = find('E', i);
            if (i == -1) {
                std::cout << "NO\n";
                return ;
            }

            i = find('N', i);
            if (i == -1) {
                std::cout << "NO\n";
                return ;
            }

            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
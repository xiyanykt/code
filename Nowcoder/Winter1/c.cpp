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

        std::vector<std::string>s(n + 1);
        for (int i = 1; i <= n; i += 1) {
            std::cin >> s[i];
            s[i] = ' ' + s[i];
        }

        std::vector<std::pair<int, int>>pos;
        std::vector<std::array<int, 4>>res;
        
        auto find = [&]() ->std::pair<int, int> {
            for (int i = 1; i <= n; i += 1) {
                for (int j = 1; j <= n; j += 1) {
                    if ((i <= n / 2 && j <= n / 2)|| s[i][j] == '0') {
                        continue;
                    }
                    return std::pair(i, j);
                }
            }
            assert(false);
            return std::pair(-1, -1);
        };

        for (int i = 1; i <= n / 2; i += 1) {
            for (int j = 1; j <= n / 2; j += 1) {
                if (s[i][j] == '1') {
                    continue;
                }
                auto [x, y] = find();
                debug(i, j, x, y);
                if (x == i) {
                    for (int k = y - 1; k >= j; k -= 1) {
                        std::swap(s[i][k + 1], s[i][k]);
                        res.push_back({i, k + 1, i, k});
                    }
                } else if (x < i) {
                    for (int k = x + 1; k <= i; k += 1) {
                        std::swap(s[k][y], s[k - 1][y]);
                        res.push_back({k, y, k - 1, y});
                    }
                    if (y > j) {
                        for (int k = y - 1; k >= j; k -= 1) {
                            std::swap(s[i][k + 1], s[i][k]);
                            res.push_back({i, k + 1, i, k});
                        }
                    } else if (y < j) {
                        assert(false);
                    }
                } else {
                    if (y > j) {
                        for (int k = y - 1; k >= j; k -= 1) {
                            std::swap(s[x][k], s[x][k + 1]);
                            res.push_back({x, k, x, k + 1});
                        }
                    } else if (y < j) {
                        for (int k = y + 1; k <= j; k += 1) {
                            std::swap(s[x][k], s[x][k - 1]);
                            res.push_back({x, k, x, k - 1});
                        }
                    }
                    for (int k = x - 1; k >= i; k -= 1) {
                        std::swap(s[k + 1][j], s[k][j]);
                        res.push_back({k + 1, j, k, j});
                    }
                }
            }
        }
        
        // for (int i = 1; i <= n; i += 1) {
        //     std::cout << s[i] << '\n';
        // }
        // debug();

        std::cout << res.size() << '\n';
        for (const auto & [a, b, c, d] : res) {
            std::cout << std::format("{} {} {} {}\n", a, b, c, d);
        }
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
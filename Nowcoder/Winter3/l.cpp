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
    std::cin >> n;

    n += 1;
    std::cout << "Yes\n";
    std::vector<std::vector<int>>t(n + 1);
    for (int l = 1, c = 1; l <= n; l += 1) {
        t[l].resize(l + 1);
        for (int i = 1; i <= l; i += 1) {
            t[l][i] = c++;
        }
    }

    // for (int i = 1; i <= n; i += 1) {
    //     for (int j = 1; j < t[i].size(); j += 1) {
    //         std::cout << t[i][j] << " \n"[j == t[i].size() - 1];
    //     }
    // }

    std::vector<int>r;
    if (n % 2 == 0) {
        for (int i = 1; i <= n; i += 1) {
            if (i % 2 == 1) {
                for (int j = 1; j < t[i].size(); j += 1) {
                    r.push_back(t[i][j]);
                }
            } else {
                for (int j = t[i].size() - 1; j >= 1; j -= 1) {
                    r.push_back(t[i][j]);
                }
            }
        }
        for (int i = n - 1; i >= 1; i -= 1) {
            if ((n - i) % 2 == 1) {
                for (int j = 1; j < t[i].size() - 1; j += 1) {
                    r.push_back(t[i][j]);
                    r.push_back(t[i + 1][j + 1]);
                }
                r.push_back(t[i].back());
            } else {
                for (int j = t[i].size() - 1; j >= 2; j -= 1) {
                    r.push_back(t[i][j]);
                    r.push_back(t[i + 1][j]);
                }
                r.push_back(t[i][1]);
            }
        }
    } else {
        for (int i = 1; i <= n; i += 1) {
            if (i % 2 == 0) {
                for (int j = 1; j < t[i].size(); j += 1) {
                    r.push_back(t[i][j]);
                }
            } else {
                for (int j = t[i].size() - 1; j >= 1; j -= 1) {
                    r.push_back(t[i][j]);
                }
            }
        }
        for (int i = n - 1; i >= 1; i -= 1) {
            if ((n - i) % 2 == 1) {
                for (int j = 1; j < t[i].size() - 1; j += 1) {
                    r.push_back(t[i][j]);
                    r.push_back(t[i + 1][j + 1]);
                }
                r.push_back(t[i].back());
            } else {
                for (int j = t[i].size() - 1; j >= 2; j -= 1) {
                    r.push_back(t[i][j]);
                    r.push_back(t[i + 1][j]);
                }
                r.push_back(t[i][1]);
            }
        }
    }

    for (const auto & c : r) {
        std::cout << c << ' ';
    }
    std::cout << '\n';
    return 0;
}
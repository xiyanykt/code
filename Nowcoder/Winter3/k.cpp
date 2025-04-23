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

    int m = 0, c = 0;
    std::vector<int>p(n);
    std::vector<std::vector<int>>a(n);
    for (int i = 0; i < n; i += 1) {
        int l;
        std::cin >> l;
        m += l;
        a[i].resize(l);
        for (auto & aij : a[i]) {
            std::cin >> aij;
        }
        for (int j = 0; j < l; j += 1) {
            for (int k = j + 1; k < l; k += 1) {
                c += a[i][k] < a[i][j];
            }
        }
        p[i] = a[i][0];
    }

    if (c > k) {
        std::cout << "No\n";
        return 0;
    }

    std::vector<int>v(n);
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1) {
            if (p[i] > p[j]) {
                v[i] += a[j].size();
            }
        }
    }

    std::vector<int>r;
    for (int t = 0; t < m; t += 1) {
        int s = -1;
        for (int i = 0; i < n; i += 1) {
            if (!a[i].empty() && v[i] + c <= k && (s == -1 || v[i] > v[s])) {
                s = i;
            }
        }

        r.push_back(a[s].front());
        a[s].erase(a[s].begin());
        c += v[s];
        for (int i = 0; i < n; i += 1) {
            if (p[i] > p[s]) {
                v[i] -= 1;
            }
        }
    }

    if (c != k) {
        std::cout << "No\n";
    } else {
        std::cout << "Yes\n";
        for (auto c : r) {
            std::cout << c << ' ';
        }
    }
    return 0;
}
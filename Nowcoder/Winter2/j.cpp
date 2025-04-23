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

const int d[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool isLeap(int y) {
    return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
}

int daysInMonth(int y, int m) {
    return d[m - 1] + (isLeap(y) && m == 2);
}

int getDay(int y, int m, int d) {
    int ans = 0;
    for (int i = 1970; i < y; i++) {
        ans += 365 + isLeap(i);
    }
    for (int i = 1; i < m; i++) {
        ans += daysInMonth(y, i);
    }
    ans += d;
    return (ans + 2) % 7 + 1;
}

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    #define int i64

    int n, h, m;
    std::cin >> n >> h >> m;

    std::set<int>a, b, c;
    for (int i = 1; i <= n; i += 1) {
        int p;
        std::string s, t;
        std::cin >> p >> s >> t;

        if ((std::string() + s[0] + s[1] + s[2] + s[3]) == std::to_string(h) && std::stoi(std::string() + s[5] + s[6]) == m) {
            auto k = std::string() + t[0] + t[1];
            if (t == "01:00:00" || k == "22" || k == "23" || k == "00") {
                c.insert(p);
            }
            if (t == "13:00:00" || k == "11" || k == "12") {
                b.insert(p);
            }
            if (t == "09:00:00" || t == "20:00:00" || k == "07" || k == "08" || k == "18" || k == "19") {
                a.insert(p);
            }
        }
    }

    std::cout << a.size() << ' ' << b.size() << ' ' << c.size() << '\n';
    return 0;
}
#include<bits/stdc++.h>
using i64 = long long;

template<class T>
constexpr bool chmax(T& x, T y) {
    if (y > x) {
        x = y;
        return true;
    }
    return false;
}

std::vector<int> divisors(int n) {
    std::vector<int>r;
    for (int x = 1; x * x <= n; x += 1) {
        if (n % x == 0) {
            r.push_back(x);
            if (x * x != n) {
                r.push_back(n / x);
            }
        }
    }
    std::sort(r.begin(), r.end());
    return r;
}

auto main() ->int32_t {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int>a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i += 1) {
        std::cin >> a[i] >> b[i];
    }

    i64 res = 0;
    auto A = divisors(a[1]), B = divisors(b[1]);
    for (const auto & u : A) {
        for (const auto & v : B) {
            int ok = 1;
            for (int i = 1; i <= n; i += 1) {
                ok &= ((a[i] % u == 0 && b[i] % v == 0) || (b[i] % u == 0 && a[i] % v == 0));
            }
            if (ok) {
                chmax(res, std::lcm<i64>(u, v));
            }
        }
    }
    std::cout << res << '\n';
    return 0;
}
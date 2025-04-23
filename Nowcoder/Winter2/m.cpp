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

template<typename T>
constexpr T power(T a, u64 b) {
    T res {1};
    for (; b != 0; b /= 2, a *= a) {
        if (b % 2 == 1) {
            res *= a;
        }
    }
    return res;
}

template<u32 P>
constexpr u32 mulMod(u32 a, u32 b) {
    return 1ULL * a * b % P;
}

template<u64 P>
constexpr u64 mulMod(u64 a, u64 b) {
    u64 res = a * b - u64(1.L * a * b / P - 0.5L) * P;
    res %= P;
    return res;
}

template<typename U, U P>
requires std::unsigned_integral<U>
struct ModIntBase {
public:
    constexpr ModIntBase() : x {0} {}

    template<typename T>
    requires std::integral<T>
    constexpr ModIntBase(T x_) : x{norm(static_cast<U>(x_ % static_cast<T>(P)))} {}

    constexpr static U norm(U x) {
        if ((x >> (8 * sizeof(U) - 1) & 1) == 1) {
            x += P;
        }
        if (x >= P) {
            x -= P;
        }
        return x;
    }

    constexpr U val() const {
        return x;
    }

    constexpr ModIntBase operator-() const {
        ModIntBase res;
        res.x = norm(P - x);
        return res;
    }

    constexpr ModIntBase inv() const {
        return power(*this, P - 2);
    }

    constexpr ModIntBase &operator*=(const ModIntBase &rhs) & {
        x = mulMod<P>(x, rhs.val());
        return *this;
    }

    constexpr ModIntBase &operator+=(const ModIntBase &rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }

    constexpr ModIntBase &operator-=(const ModIntBase &rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }

    constexpr ModIntBase &operator/=(const ModIntBase &rhs) & {
        return *this *= rhs.inv();
    }

    friend constexpr ModIntBase operator*(ModIntBase lhs, const ModIntBase &rhs) {
        lhs *= rhs;
        return lhs;
    }

    friend constexpr ModIntBase operator+(ModIntBase lhs, const ModIntBase &rhs) {
        lhs += rhs;
        return lhs;
    }

    friend constexpr ModIntBase operator-(ModIntBase lhs, const ModIntBase &rhs) {
        lhs -= rhs;
        return lhs;
    }

    friend constexpr ModIntBase operator/(ModIntBase lhs, const ModIntBase &rhs) {
        lhs /= rhs;
        return lhs;
    }

    friend constexpr std::ostream &operator<<(std::ostream &os, const ModIntBase &a) {
        return os << a.val();
    }

    friend constexpr bool operator==(ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() == rhs.val();
    }

    friend constexpr bool operator!=(ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() != rhs.val();
    }

    friend constexpr bool operator<(ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() < rhs.val();
    }

private:
    U x;
};

template<u32 P>
using ModInt = ModIntBase<u32, P>;

template<u64 P>
using ModInt64 = ModIntBase<u64, P>;
constexpr u32 P = u32(1E9) + 7;
using Z = ModInt<P>;
constexpr int M = 2E5;

struct Comb {
    std::vector<Z>fac, ifac;

    Comb() {}
    Comb(int n) {
        fac.resize(n + 1), ifac.resize(n + 1);
        fac[0] = ifac[0] = 1ULL;
        for (int i = 1; i <= n; i += 1) {
            fac[i] = fac[i - 1] * i;
        }
        ifac[n] = fac[n].inv();
        for (int i = n; i >= 1; i -= 1) {
            ifac[i - 1] = ifac[i] * i;
        }
    }

    Z C(int n, int m) {
        if (m > n or n < 0 or m < 0) {
            return Z(0);
        }
        return fac[n] * ifac[m] * ifac[n - m];
    }

    Z Lucas(i64 n, i64 m) {
        return (m == 0 ? Z(1) : C(n % P, m % P) * Lucas(n / P, m / P));
    }
} comb(M);

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto solve = [&]() {
        int n;
        std::cin >> n;

        std::vector<std::string>s(4);
        for (int i = 1; i <= 3; i += 1) {
            std::cin >> s[i];
            s[i] = ' ' + s[i];
        }

        std::set<int>f[3];
        for (int i = 1; i <= 3; i += 1) {
            for (int j = 1; j <= n; j += 1) {
                if (s[i][j] != '?') {
                    f[j % 3].insert(s[i][j] - '0');
                }
            }
        }

        if (f[0].size() > 3 || f[1].size() > 3 || f[2].size() > 3) {
            std::cout << 0 << '\n';
            return ;
        }

        for (int d = 1; d <= 9; d += 1) {
            if ((f[0].contains(d) + f[1].contains(d) + f[2].contains(d)) >= 2) {
                std::cout << 0 << '\n';
                return ;
            }
        }

        for (int j = 1; j <= n; j += 1) {
            std::set<int>r;
            for (int i = 1; i <= 3; i += 1) {
                if (s[i][j] == '?') {
                    continue;
                }
                if (r.contains(s[i][j] - '0')) {
                    std::cout << 0 << '\n';
                    return ;
                }
                r.insert(s[i][j] - '0');
            }
        }

        std::vector<int>c(n + 1);
        for (int j = 1; j <= n; j += 1) {
            for (int i = 1; i <= 3; i += 1) {
                c[j] += s[i][j] == '?';
            }
        }

        Z res = 1;
        int a = 0;
        std::vector<int>h(3);
        for (int i = 0; i <= 2; i += 1) {
            h[i] = 3 - f[i].size();
            a += h[i];
        }
        for (int i = 1; i <= n; i += 1) {
            res *= comb.fac[c[i]];
        }

        res *= comb.C(a, h[0]) * comb.C(a - h[0], h[1]);

        std::cout << res << '\n';
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
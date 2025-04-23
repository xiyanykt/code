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

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

u64 rand(i64 l, i64 r) {
    return std::uniform_int_distribution<u64>(l, r)(rng);
}

static constexpr u64 Mod = (1ull << 61) - 1;

static constexpr u64 add(u64 a, u64 b) {
    u64 c = a + b;
    if (c >= Mod) {
        c -= Mod;
    }
    return c;
}

static constexpr u64 mul(u64 a, u64 b) {
    __uint128_t c = static_cast<__uint128_t>(a) * b;
    return add(c >> 61, c & Mod);
}

constexpr int Kn = 1E6;
u64 pw[Kn + 1];
u64 htt = rand(Mod / 3, Mod / 2);

struct Hash : public std::vector<u64> {
    Hash() = default;
    Hash(const std::string& s) {
        int n = s.size();
        this->resize(n + 1);
        for (int i = 1; i <= n; i += 1) {
            (*this)[i] = add(mul((*this)[i - 1], htt), int(s[i - 1]));
        }
    }

    constexpr u64 rangeQuery(int l, int r) const {
        return add((*this)[r], Mod - mul((*this)[l - 1], pw[r - l + 1]));
    }
};

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    pw[0] = 1;
    for (int i = 1; i <= Kn; i += 1) {
        pw[i] = mul(pw[i - 1], htt);
    }

    auto solve = [&]() {
        std::string s;
        std::cin >> s;

        int n = s.length();

        Hash f(s);
        std::ranges::reverse(s);
        Hash g(s);
        std::ranges::reverse(s);

        if (f.rangeQuery(1, n) == g.rangeQuery(1, n)) {
            std::cout << 0 << '\n';
            return ;
        }

        constexpr int Kn = 26;
        std::vector<std::array<int, Kn>>cnt(n + 1);
        for (int i = 1; i <= n; i += 1) {
            for (int k = 0; k < Kn; k += 1) {
                cnt[i][k] += cnt[i - 1][k];
            }
            cnt[i][s[i - 1] - 'a'] += 1;
        }

        auto ok = [&](int fl, int fr, int gl, int gr) {
            return f.rangeQuery(fl, fr) == g.rangeQuery(n - gr + 1, n - gl + 1);
        };

        auto rangeQuery = [&](int fl, int fr, int gl, int gr, int k) ->std::pair<int, int> {
            return {cnt[fr][k] - cnt[fl - 1][k], cnt[gr][k] - cnt[gl - 1][k]};
        };

        int i = 1;
        while (i <= n / 2 && ok(1, i, n - i + 1, n)) {
            i += 1;
        }

        for (int len = 1; ; len += 1) {
            int r = i + len - 1;
            if (r < n / 2) {
                if (!ok(i + len, n - i + 1 - len, i + len, n - i + 1 - len)) {
                    debug(len, i + len, n - i + 1 - len);
                    continue;
                }
                bool ok = true;
                for (int k = 0; k < Kn; k += 1) {
                    auto [x, y] = rangeQuery(i, i + len - 1, n - i + 1 - len + 1, n - i + 1, k);
                    if (x != y) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    std::cout << len << '\n';
                    return ;
                }
            } else {
                // [i + len, n - i + 1]
                bool ok = true;
                int h = (n - i + 1) - (i + len) + 1;
                for (int k = 0; k < Kn; k += 1) {
                    auto [x, y] = rangeQuery(i, i + len - 1, i + len, n - i + 1, k);
                    if (x < y || (x - y) % 2 != 0) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    std::cout << len << '\n';
                    return ;
                }
            }
        }
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
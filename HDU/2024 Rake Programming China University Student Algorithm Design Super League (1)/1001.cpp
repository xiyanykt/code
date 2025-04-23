#include<bits/stdc++.h>

using i64 = int64_t;

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int rand(int l, int r) {
    return std::uniform_int_distribution<int>(l, r)(rng);
}

bool isPri(int n) {
    if (n <= 1)return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0)return false;
    }
    return true;
}

int gene(int l, int r) {
    int x = rand(l, r);
    while (!isPri(x)) {
        x += 1;
    }
    return x;
}

// const int MOD1 = gene(1e7, 1e8);
// const int MOD2 = gene(1e8, 1e9);
const int MOD1 = 1e9 + 7;
const int MOD2 = 998244353;
const int BASE1 = 17 + rand(0, 13);
const int BASE2 = 37 + rand(0, 13);

// template<class T>
// void hash_combine(std::size_t& seed, const T& v) {
//     std::hash<T> hasher;
//     seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
// }

// struct PairHash {
//     template<class T1, class T2>
//     std::size_t operator()(const std::pair<T1, T2>& pair)const {
//         std::size_t seed = 0;
//         hash_combine(seed, pair.first), hash_combine(seed, pair.second);
//         return seed;
//     }
// };

// struct PairEqual {
//     template<class T1, class T2>
//     bool operator()(const std::pair<T1, T2>& lsh, const std::pair<T1, T2>& rsh)const {
//         return lsh.first == rsh.first and lsh.second == rsh.second;
//     }
// };

i64 iPair(const std::pair<int, int>& v) {
    return static_cast<i64>(v.first) << 32LL | v.second;
}

struct HashBase {
    std::vector<int>P, p;

    HashBase() {}

    HashBase(int n) {
        P.resize(n + 1), p.resize(n + 1);
        P[0] = p[0] = 1;
        for (int i = 1; i <= n; i += 1) {
            P[i] = 1LL * P[i - 1] * BASE1 % MOD1;
            p[i] = 1LL * p[i - 1] * BASE2 % MOD2;
        }
    }
};

HashBase BASE(3E6);

struct Hash {
    std::vector<int>H, h;

    Hash() {}

    Hash(const std::string& s) {
        int n = s.size();
        H.resize(n + 1), h.resize(n + 1);
        for (int i = 1; i <= n; i += 1) {
            H[i] = (1LL * H[i - 1] * BASE1 % MOD1 + (s[i - 1])) % MOD1;
            h[i] = (1LL * h[i - 1] * BASE2 % MOD2 + (s[i - 1])) % MOD2;
        }
    }

    std::pair<int, int> query(int l, int r) {
        int a = (1LL * H[r] - 1LL * H[l - 1] * BASE.P[r - l + 1] % MOD1 + MOD1) % MOD1;
        int b = (1LL * h[r] - 1LL * h[l - 1] * BASE.p[r - l + 1] % MOD2 + MOD2) % MOD2;
        return {a, b};
    }
};

#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) (void)42
#endif

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto solve = [&]() {
        std::string a, b;
        std::cin >> a >> b;

        int n = a.size(), m = b.size();

        a += a;

        Hash x(a);
        std::set<std::pair<int, int>>S;
        for (int i = 1; i <= n; i += 1) {
            S.insert(x.query(i, i + n - 1));
        }

        int ans = 0;
        Hash y(b);
        for (int i = 1; i + n - 1 <= m; i += 1) {
            if (S.contains(y.query(i, i + n - 1))) {
                ans += 1;
            }
        }
        std::cout << ans << "\n";
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
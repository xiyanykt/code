#include<bits/stdc++.h>

#pragma GCC optimize("O2")
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
#pragma GCC target("sse4,popcnt,abm,mmx")

using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;

#ifndef ONLINE_JUDGE
#include "algo\debug.hpp"
#else
#define debug(...) (void)42
#endif

template<class T>
void chmax(T& x, T y) {
    x = std::max(x, y);
}

template<class T>
void chmin(T& x, T y) {
    x = std::min(x, y);
}

template<class T>
constexpr T power(T a, i64 b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

constexpr i64 mul(i64 a, i64 b, i64 p) {
    i64 res = a * b - i64(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}
template<i64 P>
struct MLong {
    i64 x;
    constexpr MLong() : x{} {}
    constexpr MLong(i64 x) : x{norm(x % getMod())} {}

    static i64 Mod;
    constexpr static i64 getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(i64 Mod_) {
        Mod = Mod_;
    }
    constexpr i64 norm(i64 x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr i64 val() const {
        return x;
    }
    explicit constexpr operator i64() const {
        return x;
    }
    constexpr MLong operator-() const {
        MLong res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MLong inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MLong &operator*=(MLong rhs) & {
        x = mul(x, rhs.x, getMod());
        return *this;
    }
    constexpr MLong &operator+=(MLong rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MLong &operator-=(MLong rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MLong &operator/=(MLong rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MLong operator*(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MLong operator+(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MLong operator-(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MLong operator/(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MLong &a) {
        i64 v;
        is >> v;
        a = MLong(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MLong &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MLong lhs, MLong rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MLong lhs, MLong rhs) {
        return lhs.val() != rhs.val();
    }
};

template<>
i64 MLong<0LL>::Mod = 1;

template<int P>
struct MInt {
    int x;
    constexpr MInt() : x{} {}
    constexpr MInt(i64 x) : x{norm(x % getMod())} {}

    static int Mod;
    constexpr static int getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(int Mod_) {
        Mod = Mod_;
    }
    constexpr int norm(int x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr int val() const {
        return x;
    }
    explicit constexpr operator int() const {
        return x;
    }
    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MInt &operator*=(MInt rhs) & {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt &operator/=(MInt rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
        i64 v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }
};

template<>
int MInt<0>::Mod = 1;

template<int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();

constexpr int P = 1E9 + 7;
using Z = MInt<P>;

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
constexpr int MOD1 = 1e9 + 7;
constexpr int MOD2 = 998244353;
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

HashBase BASE(1E6);

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

Z cal(const std::string& s) {
    int n = s.size();
    std::vector<Z>dp(26);
    for (int i = 0; i < n; i += 1) {
        Z sum = 1;
        std::vector<Z>ndp(26);
        for (int j = 0; j <= 25; j += 1) {
            sum += (ndp[j] = dp[j]);
        }
        ndp[s[i] - 'a'] = sum;
        dp.swap(ndp);
    }
    return std::accumulate(dp.begin(), dp.end(), Z(0));
}

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    return 0;
}
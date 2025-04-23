#include<bits/stdc++.h>

using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;

#ifndef ONLINE_JUDGE
#include "algo\debug.hpp"
#else
#define debug(...) (void)42
#endif

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

constexpr int P = 998244353;
using Z = MInt<P>;

constexpr int $N = 2E5;

struct Comb {
    int n;
    std::vector<Z>fac, ifac;

    Comb() {}
    Comb(int n) {
        this->n = n;
        fac.resize(n + 1), ifac.resize(n + 1);
        fac[0] = 1;
        for (int i = 1; i <= n; i += 1) {
            fac[i] = fac[i - 1] * i;
        }
        ifac[n] = fac[n].inv();
        for (int i = n; i >= 1; i -= 1) {
            ifac[i - 1] = ifac[i] * i;
        }
    }

    Z C(int n, int m) {
        return fac[n] * ifac[m] * ifac[n - m];
    }

    Z Lucas(i64 n, i64 m) {
        return (m == 0 ? 1 : C(n % P, m % P) * Lucas(n / P, m / P));
    }
} comb($N);

struct LCT {
    std::vector<std::vector<int>>son;
    std::vector<int>par, siz, rev;

    LCT () {}
    LCT(int n) {
        son.assign(2, std::vector<int>(n + 1));
        par.assign(n + 1, 0);
        siz.assign(n + 1, 1);
        rev.assign(n + 1, 0);
    }

    void reverse(int x) {
        std::swap(son[0][x], son[1][x]);
        rev[x] ^= 1;
    }

    void push(int x) {
        if (rev[x]) {
            reverse(son[0][x]);
            reverse(son[1][x]);
            rev[x] = 0;
        }
    }

    void pull(int x) {
        siz[x] = siz[son[0][x]] + siz[son[1][x]] + 1;
    }

    bool isRoot(int x) {
        return (not par[x]) or (son[0][par[x]] != x and son[1][par[x]] != x);
    }

    int pos(int x) {
        return x == son[1][par[x]];
    }

    void update(int x) {
        if (not isRoot(x)) {
            update(par[x]);
        }
        push(x);
    }

    void rotate(int t) {
        int q = par[t];
        int x = !pos(t);
        son[!x][q] = son[x][t];
        if (son[x][t]) {
            par[son[x][t]] = q;
        }
        par[t] = par[q];
        if (not isRoot(q)) {
            son[pos(q)][par[q]] = t;
        }
        son[x][t] = q;
        par[q] = t;
        pull(q);
    }

    void Splay(int t) {
        update(t);
        while (not isRoot(t)) {
            if (not isRoot(par[t])) {
                rotate((pos(t) == pos(par[t])) ? par[t] : t);
            }
            rotate(t);
        }
        pull(t);
    }

    void access(int t) {
        for (int i = t, q = 0; i; q = i, i = par[i]) {
            Splay(i);
            son[1][i] = q;
            pull(i);
        }
        Splay(t);
    }

    int find(int x) {
        access(x);
        Splay(x);
        while (son[0][x]) {
            push(x);
            x = son[0][x];
        }
        Splay(x);
        return x;
    }

    void makeRoot(int t) {
        access(t);
        Splay(t);
        reverse(t);
    }

    void link(int x, int y) {
        makeRoot(x);
        if (find(y) != x) {
            par[x] = y;
        }
    }
};

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cout << std::fixed << std::setprecision(13);

    int n, q;
    std::cin >> n >> q;

    LCT lct(n);
    std::vector adj(n + 1, std::vector<int>());
    for (int i = 2; i <= n; i += 1) {
        int x;
        std::cin >> x;
        lct.link(i, x);
        adj[x].push_back(i);
    }

    std::vector<int>siz(n + 1);
    auto work = [&](auto && self, int u, int par) ->void{
        siz[u] += 1;
        for (const auto & v : adj[u]) {
            if (v == par) {
                continue;
            }
            self(self, v, u);
            siz[u] += siz[v];
        }
    };
    work(work, 1, 0);


    Z ans = comb.fac[n];
    for (int i = 1; i <= n; i += 1) {
        ans *= Z(siz[i]).inv();
    }

    std::vector<int>tag(n + 1);

    auto cg = [&](int x) {
        tag[x] ^= 1;
        if (tag[x]) {
            ans *= Z(siz[x]);
        } else {
            ans *= Z(siz[x]).inv();
        }
    };

    auto find = [&](int x)->int {
        while (lct.son[0][x]) {
            x = lct.son[0][x];
        }
        return x;
    };

    auto modify = [&](int x) {
        for (int i = x, q = 0; i; q = i, i = lct.par[i]) {
            lct.Splay(i);
            if (lct.son[1][i]) {
                cg(find(lct.son[1][i]));
            }
            if (q) {
                cg(find(q));
            }
            lct.son[1][i] = q;
            lct.pull(i);
        }
    };

    while (q--) {
        int x;
        std::cin >> x;
        modify(x);
        std::cout << ans << "\n";
    }

    return 0;
}

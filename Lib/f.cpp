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
#define debug(...) (void)13
#endif

template<class T>
constexpr bool chmax (T& x, T y) {
    if (y > x) {
        x = y;
        return true;
    }
    return false;
}

template<class T>
constexpr bool chmin (T& x, T y) {
    if (y < x) {
        x = y;
        return true;
    }
    return false;
}

struct RevocableDSU {
    std::vector<int>par, s1, s2;
    std::vector<std::pair<int, int>>stk;

    RevocableDSU() = default;
    RevocableDSU(int n) {
        par.resize(n + 1);
        s1.resize(n + 1);
        s2.resize(n + 1);
        for (int i = 1; i <= n / 2; i += 1) {
            s1[i] = 1;
        }
        for (int i = n / 2 + 1; i <= n; i += 1) {
            s2[i] = 1;
        }
        std::iota(par.begin(), par.end(), 0);
        stk.clear();
    } 

    int find(int x) {
        while (x != par[x]) {
            x = par[x];
        }
        return x;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    bool merge(int x, int y, i64& ans) {
        x = find(x), y = find(y);
        if (x == y) {
            return false;
        }
        if (s1[x] + s2[x] < s1[y] + s2[y]) {
            std::swap(x, y);
        }
        ans -= 1LL * s1[x] * s2[x];
        ans -= 1LL * s1[y] * s2[y];
        par[y] = x;
        s1[x] += s1[y];
        s2[x] += s2[y];
        ans += 1LL * s1[x] * s2[x];
        stk.emplace_back(x, y);
        return true;
    }

    int version() {
        return stk.size();
    }

    void rollback(int v, i64& ans) {
        while (int(stk.size()) > v) {
            auto [x, y] = stk.back();
            stk.pop_back();
            ans -= 1LL * s1[x] * s2[x];
            s1[x] -= s1[y];
            s2[x] -= s2[y];
            par[y] = y;
            ans += 1LL * s1[x] * s2[x];
            ans += 1LL * s1[y] * s2[y];
        }
    }
};

constexpr int K = 3E5;

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    std::cin >> q;

    std::vector<std::vector<std::pair<int, int>>>t(4 << std::__lg(q));
    auto add = [&](int L, int R, int u, int v) {
        if (L > R) {
            return ;
        }
        debug(L, R, u, v);
        auto dfs = [&](auto && self, int p, int l, int r) {
            if (l > R || r < L) {
                return;
            }
            if (L <= l && r <= R) {
                t[p].emplace_back(u, v);
                return ;
            }
            int mid = (l + r) >> 1;
            self(self, p << 1, l, mid);
            self(self, p << 1 | 1, mid + 1, r);
        };
        dfs(dfs, 1, 1, q);
    };

    std::map<std::pair<int, int>, int>lst;
    for (int i = 1; i <= q; i += 1) {
        int x, y;
        std::cin >> x >> y;
        auto it = lst.find({x, y});
        if (it != lst.end()) {
            add(it->second, i - 1, x, y);
            lst.erase(it);
        } else {
            lst[{x, y}] = i;
        }
    }

    for (auto [v, i] : lst) {
        auto [x, y] = v;
        add(i, q, x, y);
    }

    i64 ans = 0;
    RevocableDSU dsu(2 * K);
    auto dfs = [&](auto && self, int p, int l, int r) ->void {
        int cur = dsu.version();
        for (auto [x, y] : t[p]) {
            dsu.merge(x, y + K, ans);
        }
        if (l == r) {
            std::cout << ans << " \n"[l == q];
        } else {
            int mid = (l + r) >> 1;
            self(self, p << 1, l, mid);
            self(self, p << 1 | 1, mid + 1, r);
        }
        dsu.rollback(cur, ans);
    };
    dfs(dfs, 1, 1, q);
    return 0;
}
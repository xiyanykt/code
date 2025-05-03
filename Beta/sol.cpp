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

struct SAM {
    static constexpr int ALPHABET = 10;
    struct Node {
        int len;
        int link;
        std::array<int, ALPHABET>next;
        Node(): len{}, link{}, next{} {}
    };

    std::vector<Node> t;
    SAM() {
        t.assign(2, Node());
        t[0].next.fill(1);
        t[0].len = -1;
    }

    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }

    int extend(int p, int x) {
        if (t[p].next[x]) {
            int q = t[p].next[x];
            if (t[q].len == t[p].len + 1) {
                return q;
            }
            int r = newNode();
            t[r].len = t[p].len + 1;
            t[r].link = t[q].link;
            t[r].next = t[q].next;
            t[q].link = r;
            while (t[p].next[x] == q) {
                t[p].next[x] = r;
                p = t[p].link;
            }
            return r;
        }
        int cur = newNode();
        t[cur].len = t[p].len + 1;
        while (not t[p].next[x]) {
            t[p].next[x] = cur;
            p = t[p].link;
        }
        t[cur].link = extend(p, x);
        return cur;
    }

    int next(int p, int x) {
        return t[p].next[x];
    }

    int link(int p) {
        return t[p].link;
    }

    int len(int p) {
        return t[p].len;
    }

    int size() {
        return t.size();
    }
};

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    SAM sam;
    std::vector<int>end{1};
    for (char c : s) {
        end.push_back(sam.extend(end.back(), c - '0'));
    }

    std::vector<i64>f(sam.size());
    for (int p : end) {
        f[p] = 1;
    }

    std::vector<std::vector<int>>adj(sam.size());
    for (int i = 2; i < sam.size(); i += 1) {
        adj[sam.link(i)].push_back(i);
    }

    i64 ans = 0;
    auto dfs = [&](auto && self, int u) ->void {
        for (int v : adj[u]) {
            self(self, v);
            f[u] += f[v];
        }
        for (int x = 0; x <= 8; x += 1) {
            int p = sam.next(u, x), q = sam.next(u, x + 1);
            while (p >= 2 && q >= 2) {
                ans += 1LL * f[p] * f[q] * (sam.len(u) - sam.len(sam.link(u)));
                p = sam.next(p, 9);
                q = sam.next(q, 0);
            }
        }
    };
    dfs(dfs, 1);

    std::cout << ans << '\n';
    return 0;
}
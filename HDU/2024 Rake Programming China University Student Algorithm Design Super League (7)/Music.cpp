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

template<class Info>
struct SegmentTree {
    int n;
    std::vector<Info>info;

    SegmentTree() {}

    SegmentTree(int n) {
        this->n = n;
        info.assign(4 << std::__lg(n), Info());
    }

    void build(const auto& a) {
        auto work = [&](auto && self, int p, int l, int r) {
            if (l == r) {
                info[p] = Info(a[l]);
                return;
            }
            int mid = l + r >> 1;
            self(self, p << 1, l, mid), self(self, p << 1 | 1, mid + 1, r);
            info[p] = info[p << 1] + info[p << 1 | 1];
        };
        work(work, 1, 1, n);
    }

    void modify(int p, int l, int r, int L, int R, const Info& v) {
        if (l > R or r < L) {
            return;
        }
        if (L <= l and r <= R) {
            info[p] = v;
            return;
        }
        int mid = l + r >> 1;
        modify(p << 1, l, mid, L, R, v), modify(p << 1 | 1, mid + 1, r, L, R, v);
        info[p] = info[p << 1] + info[p << 1 | 1];
    }
    void modify(int p, const Info& v) {
        modify(1, 1, n, p, p, v);
    }

    Info rangeQuery(int p, int l, int r, int L, int R) {
        if (l > R or r < L) {
            return Info();
        }
        if (L <= l and r <= R) {
            return info[p];
        }
        int mid = l + r >> 1;
        return rangeQuery(p << 1, l, mid, L, R) + rangeQuery(p << 1 | 1, mid + 1, r, L, R);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 1, n, l, r);
    }

    template<class F>
    int findFirst(int p, int l, int r, int L, int R, F pred) {
        if (l > R or r < L or not pred(info[p])) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        int mid = l + r >> 1;
        int res = findFirst(p << 1, l, mid, L, R, pred);
        return res == -1 ? findFirst(p << 1 | 1, mid + 1, r, L, R, pred) : res;
    }
    template<class F>
    int findFirst(int l, int r, F pred) {
        return findFirst(1, 1, n, l, r, pred);
    }

    template<class F>
    int findLast(int p, int l, int r, int L, int R, F pred) {
        if (l > R or r < L or not pred(info[p])) {
            return -1;
        }
        if (l == r) {
            return r;
        }
        int mid = l + r >> 1;
        int res = findLast(p << 1 | 1, mid + 1, r, L, R, pred);
        return res == -1 ? findLast(p << 1, l, mid, L, R, pred) : res;
    }
    template<class F>
    int findLast(int l, int r, F pred) {
        return findLast(1, 1, n, l, r, pred);
    }
};

constexpr int inf = 1E9;

struct Info {
    int val = 0;
};
Info operator+(const Info& a, const Info& b) {
    return {std::max(a.val, b.val)};
}

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto solve = [&]() {
        int n;
        i64 m, k;
        std::cin >> n >> m >> k;

        std::vector<i64>a(n + 1), dis;
        dis.push_back(0);
        for (int i = 1; i <= n; i += 1) {
            std::cin >> a[i];
            dis.push_back(a[i]);
            dis.push_back(a[i] - k);
            dis.push_back(a[i] + k);
        }

        std::sort(dis.begin() + 1, dis.end());
        dis.erase(std::unique(dis.begin() + 1, dis.end()), dis.end());

        auto Index = [&](i64 x)->int{
            return std::lower_bound(dis.begin() + 1, dis.end(), x) - dis.begin();
        };

        int M = dis.size();

        SegmentTree<Info>seg(M);
        std::vector pref(n + 1, std::vector<int>(2));
        for (int i = 1; i <= n; i += 1) {
            auto u = Index(a[i] - k);
            auto v = Index(a[i] + k);
            auto x = Index(a[i]);
            pref[i][0] = seg.rangeQuery(u, x).val;
            pref[i][1] = seg.rangeQuery(x, v).val;
            seg.modify(x, {i});
        }

        int q;
        std::cin >> q;
        std::vector<int>f(n + 1);
        while (q--) {
            int l, r;
            std::cin >> l >> r;

            int ans = 0;

            for (int i = l; i <= r; i += 1) {
                f[i] = std::max(f[pref[i][0]], f[pref[i][1]]) + 1;
                chmax(ans, f[i]);
            }
            std::fill(f.begin() + l, f.begin() + r + 1, 0);
            std::cout << (r - l + 1 - ans) << "\n";
        }

    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
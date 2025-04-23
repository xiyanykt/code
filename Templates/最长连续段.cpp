#include<bits/stdc++.h>

using i64 = long long;

template<class Info, class Tag>
struct LazySegmentTree {
    int n;
    std::vector<Info>info;
    std::vector<Tag>tag;

    LazySegmentTree () {}
    LazySegmentTree (int n) {
        this->n = n;
        info.assign(4 << std::__lg(n), Info()), tag.assign(4 << std::__lg(n), Tag());
    }

    template<typename T>
    void build(const std::vector<T>& a) {
        auto work = [&](auto && self, int p, int l, int r) {
            if (l == r) {
                info[p] = Info(a[l]);
                return;
            }
            int mid = std::midpoint(l, r);
            self(self, p << 1, l, mid), self(self, p << 1 | 1, mid + 1, r);
            info[p] = info[p << 1] + info[p << 1 | 1];
        };
        work(work, 1, 1, n);
    }

    void apply(int p, const Tag& v) {
        info[p].apply(v), tag[p].apply(v);
    }
    void pull(int p) {
        apply(p << 1, tag[p]), apply(p << 1 | 1, tag[p]);
        tag[p] = Tag();
    }

    void modify(int p, int l, int r, int L, int R, const Info& v) {
        if (l > R or r < L) {
            return;
        }
        if (L <= l and r <= R) {
            info[p] = v;
            return;
        }
        pull(p);
        int mid = std::midpoint(l, r);
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
        pull(p);
        int mid = std::midpoint(l, r);
        return rangeQuery(p << 1, l, mid, L, R) + rangeQuery(p << 1 | 1, mid + 1, r, L, R);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 1, n, l, r);
    }

    void rangeApply(int p, int l, int r, int L, int R, const Tag& v) {
        if (l > R or r < L) {
            return;
        }
        if (L <= l and r <= R) {
            apply(p, v);
            return;
        }
        pull(p);
        int mid = std::midpoint(l, r);
        rangeApply(p << 1, l, mid, L, R, v), rangeApply(p << 1 | 1, mid + 1, r, L, R, v);
        info[p] = info[p << 1] + info[p << 1 | 1];
    }
    void rangeApply(int l, int r, const Tag& v) {
        rangeApply(1, 1, n, l, r, v);
    }

    template<class F>
    int findFirst(int p, int l, int r, int L, int R, F pred) {
        if (l > R or r < L or not pred(info[p])) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        pull(p);
        int mid = std::midpoint(l, r);
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
            return l;
        }
        pull(p);
        int mid = std::midpoint(l, r);
        int res = findLast(p << 1 | 1, mid + 1, r, L, R, pred);
        return res == -1 ? findLast(p << 1, l, mid, L, R, pred) : res;
    }
    template<class F>
    int findLast(int l, int r, F pred) {
        return findLast(1, 1, n, l, r, pred);
    }
};

constexpr i64 inf = 1E18;

struct Tag {
    int rev = 0;
    void apply(const Tag& t) {
        rev ^= t.rev;
    }
};
struct Info {
    int len = 0, S = 0, P = 0;
    std::array<int, 2>u{0, 0};
    std::array<int, 2>v{0, 0};
    void apply(const Tag& t) {
        if (t.rev) {
            std::swap(S, P);
            std::swap(u, v);
        }
    }
};
Info operator+(const Info& a, const Info& b) {
    if (a.len == 0) {
        return b;
    }
    if (b.len == 0) {
        return a;
    }
    Info c {};
    c.len = a.len + b.len;
    c.S = std::max({a.S, b.S, a.u[1] + b.u[0]});
    c.P = std::max({a.P, b.P, a.v[1] + b.v[0]});
    c.u[0] = a.u[0] == a.len ? a.len + b.u[0] : a.u[0];
    c.u[1] = b.u[1] == b.len ? a.u[1] + b.len : b.u[1];
    c.v[0] = a.v[0] == a.len ? a.len + b.v[0] : a.v[0];
    c.v[1] = b.v[1] == b.len ? b.len + a.v[1] : b.v[1];
    return c;
}

#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) (void)42
#endif

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::string s;
    std::cin >> s;
    s = " " + s;

    LazySegmentTree<Info, Tag>seg(n);
    for (int i = 1; i <= n; i += 1) {
        int j = s[i] - '0';
        seg.modify(i, {1, j, j ^ 1, {j, j}, {j ^ 1, j ^ 1}});
    }

    while (q--) {
        int o, l, r;
        std::cin >> o >> l >> r;
        if (o == 1) {
            seg.rangeApply(l, r, {1});
        } else {
            auto p = seg.rangeQuery(l, r);
            std::cout << (p.S) << "\n";
        }
    }
    return 0;
}
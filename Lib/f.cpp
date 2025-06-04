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

template<class Info, class Tag>
requires requires(Info info, Tag tag) {info.apply(tag); tag.apply(tag);}
struct LazySegmentTree {
    int n;
    std::vector<Info>info;
    std::vector<Tag>tag;

    LazySegmentTree() = default;
    LazySegmentTree(int n): n{n}, info(4 << std::__lg(n), Info()), tag(4 << std::__lg(n), Tag()) {}

    LazySegmentTree (const std::vector<Info> & a) {
        int n = a.size() - 1;
        this->n = n;
        info.assign(4 << std::__lg(n), Info());
        tag.assign(4 << std::__lg(n), Tag());
        auto work = [&](auto && self, int p, int l, int r) {
            if (l == r) {
                info[p] = Info(a[l]);
                return;
            }
            int mid = (l + r) >> 1;
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
        int mid = (l + r) >> 1;
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
        int mid = (l + r) >> 1;
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
        int mid = (l + r) >> 1;
        rangeApply(p << 1, l, mid, L, R, v), rangeApply(p << 1 | 1, mid + 1, r, L, R, v);
        info[p] = info[p << 1] + info[p << 1 | 1];
    }

    void rangeApply(int l, int r, const Tag& v) {
        rangeApply(1, 1, n, l, r, v);
    }
};

struct Tag {
    int add = 0;
    void apply(Tag t) {
        add += t.add;
    }
};

struct Info {
    int v = 0;
    int p = 0;
    void apply(Tag t) {
        v += t.add;
    }

    friend Info operator+(Info a, Info b) {
        return a.v >= b.v ? a : b;
    }
};

struct Node {
    int l = 0, r = 0;
    mutable int c = 0;
    Node(int l, int r, int c): l{l}, r{r}, c{c} {}

    friend std::strong_ordering operator<=>(Node lsh, Node rsh) {
        return lsh.l <=> rsh.l;
    }
};

void solve () {
    int n, m;
    std::cin >> n >> m;

    std::vector<int>a(n + 1);
    for (int i = 1; i <= n; i += 1) {
        std::cin >> a[i];
        a[i] -= i;
    }

    LazySegmentTree<Info, Tag>seg(2 * n);
    for (int i = 1; i <= 2 * n; i += 1) {
        seg.modify(i, {0, i});
    }
    for (int i = 1; i <= n; i += 1) {
        seg.rangeApply(a[i] + i, a[i] + i, {1});
    }

    std::set<Node>odt;
    for (int i = 1; i <= n; i += 1) {
        odt.insert(Node(i, i, a[i]));
    }

    auto split = [&](int p) {
        auto it = odt.lower_bound(Node(p, 0, 0));
        if (it != odt.end() && it->l == p) {
            return it;
        }
        --it;
        int l = it->l, r = it->r, c = it->c;
        odt.erase(it);
        odt.insert(Node(l, p - 1, c));
        return odt.insert(Node(p, r, c)).first;
    };

    auto query = [&]() {
        auto [v, p] = seg.info[1];
        std::cout << p << ' ' << v << '\n';
    };

    query();
    for (int i = 1; i <= m; i += 1) {
        int l, r, d;
        std::cin >> l >> r >> d;

        auto itr = split(r + 1), itl = split(l);
        for (; itl != itr; itl = odt.erase(itl)) {
            seg.rangeApply(itl->c + itl->l, itl->c + itl->r, {-1});
        }
        d -= l;
        seg.rangeApply(d + l, d + r, {1});
        odt.insert(Node(l, r, d));
        query();
    }
}

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
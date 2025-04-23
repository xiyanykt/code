#include<bits/stdc++.h>

using i64 = int64_t;

template<class Info>
struct SegmentTree {
    int n;
    std::vector<Info>info;

    SegmentTree() {}

    SegmentTree(int n) {
        this->n = n;
        info.assign(4 << std::__lg(n), Info());
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

    void modify(int p, int l, int r, int L, int R, const Info& v) {
        if (l > R or r < L) {
            return;
        }
        if (L <= l and r <= R) {
            info[p] = v;
            return;
        }
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
        int mid = std::midpoint(l, r);
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
            return r;
        }
        int mid = std::midpoint(l, r);
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
    i64 sum = 0, ans = -inf, l = -inf, r = -inf;
};
Info operator+(const Info& a, const Info& b) {
    Info c {};
    c.sum = a.sum + b.sum;
    c.ans = std::max({a.ans, b.ans, a.r + b.l});
    c.r = std::max(b.r, a.r + b.sum);
    c.l = std::max(a.l, b.l + a.sum);
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

    auto solve = [&]() {
        int n, k, x;
        std::cin >> n >> k >> x;

        if (x < 0) {
            x = -x;
            k = n - k;
        }

        std::vector<int>a(n + 1);
        for (int i = 1; i <= n; i += 1) {
            std::cin >> a[i];
        }

        SegmentTree<Info>seg(n);
        for (int i = 1; i <= n; i += 1) {
            if (i <= k) {
                seg.modify(i, {a[i] + x, a[i] + x, a[i] + x, a[i] + x});
            } else {
                seg.modify(i, {a[i] - x, a[i] - x, a[i] - x, a[i] - x});
            }
        }

        i64 ans = seg.info[1].ans;
        for (int i = k + 1; i <= n; i += 1) {
            seg.modify(i, {a[i] + x, a[i] + x, a[i] + x, a[i] + x});
            seg.modify(i - k, {a[i - k] - x, a[i - k] - x, a[i - k] - x, a[i - k] - x});
            ans = std::max(ans, seg.info[1].ans);
        }

        std::cout << (std::max(0LL, ans)) << "\n";
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
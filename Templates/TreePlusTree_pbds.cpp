#include<bits/stdc++.h>

using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;

// #include<bits/extc++.h>
#include<ext/pb_ds/assoc_container.hpp>
// #include<ext/pb_ds/tree_policy.hpp>
// #include<ext/pb_ds/hash_policy.hpp>
// #include<ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;

template<class KT, class VT = null_type>
using RBT = tree<KT, VT, std::less<KT>, rb_tree_tag, tree_order_statistics_node_update>;

#ifndef ONLINE_JUDGE
#include "algo\debug.hpp"
#else
#define debug(...) (void)42
#endif

constexpr int inf = INT_MAX;

int tot = 1;

void add(auto&rec, int x) {
    rec.insert({x, tot++});
}

void del(auto&rec, int x) {
    rec.erase(rec.upper_bound({x, 0}));
}

int getrank(const auto & rec, int x) {
    return (int)rec.order_of_key({x, 0});
}

int find(const auto & rec, int k) {
    auto it = rec.find_by_order(k);
    return it->first;
}

int pref(const auto & rec, int x) {
    auto it = rec.lower_bound({x, 0});
    return (std::prev(it))->first;
}

int surf(const auto & rec, int x) {
    auto it = rec.upper_bound({x, inf});
    return it->first;
}

struct Info {
    RBT<std::pair<int, int>>rec;
    Info() {
        rec.insert({ -inf, 0});
        rec.insert({inf, inf});
    }
};

Info operator+(const Info& a, const Info& b) {
    if (a.rec.size() == 2) {
        return b;
    }
    if (b.rec.size() == 2) {
        return a;
    }
    Info c {};
    if (a.rec.size() > b.rec.size()) {
        c.rec = a.rec;
        for (const auto & v : b.rec) {
            c.rec.insert(v);
        }
    } else {
        c.rec = b.rec;
        for (const auto & v : a.rec) {
            c.rec.insert(v);
        }
    }
    return c;
}

constexpr int M = 5E4;
Info info[4 << std::__lg(M)];
int a[M + 1];

void build(int p, int l, int r) {
    for (int j = l; j <= r; j += 1) {
        info[p].rec.insert({a[j], j});
    }
    if (l == r) {
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
}

void update(int p, int l, int r, int x, int v) {
    del(info[p].rec, a[x]);
    info[p].rec.insert({v, x});
    if (l == r) {
        return;
    }
    int mid = l + r >> 1;
    if (x <= mid) {
        update(p << 1, l, mid, x, v);
    } else {
        update(p << 1 | 1, mid + 1, r, x, v);
    }
}

int QueryPref(int p, int l, int r, int L, int R, int k) {
    if (l > R or r < L) {
        return -inf;
    }
    if (L <= l and r <= R) {
        return pref(info[p].rec, k);
    }
    int mid = l + r >> 1;
    return std::max(QueryPref(p << 1, l, mid, L, R, k), QueryPref(p << 1 | 1, mid + 1, r, L, R, k));
}

int QuerySurf(int p, int l, int r, int L, int R, int k) {
    if (l > R or r < L) {
        return inf;
    }
    if (L <= l and r <= R) {
        return surf(info[p].rec, k);
    }
    int mid = l + r >> 1;
    return std::min(QuerySurf(p << 1, l, mid, L, R, k), QuerySurf(p << 1 | 1, mid + 1, r, L, R, k));
}

int QueryRank(int p, int l, int r, int L, int R, int k) {
    if (l > R or r < L) {
        return 0;
    }
    if (L <= l and r <= R) {
        return getrank(info[p].rec, k);
    }
    int mid = l + r >> 1;
    return QueryRank(p << 1, l, mid, L, R, k) + QueryRank(p << 1 | 1, mid + 1, r, L, R, k);
}

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    for (int i = 1; i <= n; i += 1) {
        std::cin >> a[i];
    }

    build(1, 1, n);

    auto QueryByOrder = [&](int l, int r, int k) {
        int lo = 0, hi = 1E8;
        // while (lo < hi) {
        //     int mid = (lo + hi + 1) / 2;
        //     if (QueryRank(1, 1, n, l, r, mid) <= k) {
        //         lo = mid;
        //     } else {
        //         hi = mid - 1;
        //     }
        // }
        return hi;
    };

    while (q--) {
        int o;
        std::cin >> o;
        if (o == 1) {
            int l, r, k;
            std::cin >> l >> r >> k;
            std::cout << (QueryRank(1, 1, n, l, r, k)) << "\n";
        } else if (o == 2) {
            int l, r, k;
            std::cin >> l >> r >> k;
            std::cout << (QueryByOrder(l, r, k)) << "\n";
        } else if (o == 3) {
            int x, k;
            std::cin >> x >> k;
            update(1, 1, n, x, k);
            a[x] = k;
        } else if (o == 4) {
            int l, r, k;
            std::cin >> l >> r >> k;
            std::cout << (QueryPref(1, 1, n, l, r, k)) << "\n";
        } else {
            int l, r, k;
            std::cin >> l >> r >> k;
            std::cout << (QuerySurf(1, 1, n, l, r, k)) << "\n";
        }
    }
    return 0;
}
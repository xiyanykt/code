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

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    auto pre = SegmentTree<std::pair<int, int>, f, e>(n + 1);
    auto suf = SegmentTree<std::pair<int, int>, f, e>(n + 1);
    for (int i = 1; i <= n; i += 1) {
        suf.set(i, {hld.left(i), hld.left(i)});
    }

    std::vector<int>ans(q + 1);
    for (int i = 1; i <= n; i += 1) {
        for (auto [l, r, e] : qry[i]) {
            auto [a, b] = pre.product(l, r + 1);
            auto [c, d] = suf.product(l, r + 1);
            if (b != -1 && d != -1) {
                int x = hld.lca(hld.seq[a], hld.seq[b], hld.seq[i]);
                int y = hld.lca(hld.seq[c], hld.seq[d], hld.seq[i]);
                ans[e] = hld.lca(x, y, hld.seq[i]);
            } else if (b != -1) {
                ans[e] = hld.lca(hld.seq[a], hld.seq[b], hld.seq[i]);
            } else {
                ans[e] = hld.lca(hld.seq[c], hld.seq[d], hld.seq[i]);
            }
        }
        pre.set(hld.seq[i], {i, i});
        suf.set(hld.seq[i], e());
    }
    return 0;
}
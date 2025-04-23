#include<bits/stdc++.h>

using i64 = long long;

#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) (void)42
#endif

struct Q {
    int l, r, e;
};

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int>a(n + 1);
    for (int i = 1; i <= n; i += 1) {
        std::cin >> a[i];
    }

    const int B = sqrt(n);
    std::vector<int>belong(n + 1);
    for (int i = 1; i <= n; i += 1) {
        belong[i] = (i - 1) / B + 1;
    }

    int q;
    std::cin >> q;
    std::vector<Q>qry(q + 1);
    for (int i = 1; i <= q; i += 1) {
        std::cin >> qry[i].l >> qry[i].r;
        qry[i].e = i;
    }

    std::sort(qry.begin() + 1, qry.end(), [&](const auto & x, const auto & y) {
        if (belong[x.l] ^ belong[y.l]) {
            return belong[x.l] < belong[y.l];
        } else if (belong[x.l] & 1) {
            return x.r < y.r;
        }
        return x.r > y.r;
    });

    const int N = 1E6;

    std::vector<int>ans(q + 1), cnt(N + 1);
    int res = 0;

    auto add = [&](int p) {
        if (cnt[a[p]] == 0) {
            res += 1;
        }
        cnt[a[p]] += 1;
    };

    auto del = [&](int p) {
        cnt[a[p]] -= 1;
        if (cnt[a[p]] == 0) {
            res -= 1;
        }
    };

    int l = 1, r = 0;
    for (int i = 1; i <= q; i += 1) {
        while (l < qry[i].l) {
            del(l++);
        }
        while (l > qry[i].l) {
            add(--l);
        }
        while (r < qry[i].r) {
            add(++r);
        }
        while (r > qry[i].r) {
            del(r--);
        }
        ans[qry[i].e] = res;
    }

    // while (L > l[i]) {
    //     add(--L);
    // }
    // while (R < r[i]) {
    //     add(++R);
    // }
    // while (L < l[i]) {
    //     del(L++);
    // }
    // while (R > r[i]) {
    //     del(R--);
    // }

    for (int i = 1; i <= q; i += 1) {
        std::cout << ans[i] << "\n";
    }
    return 0;
}
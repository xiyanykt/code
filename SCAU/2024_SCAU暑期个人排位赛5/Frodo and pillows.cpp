#include<bits/stdc++.h>

using i64 = int64_t;

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

#define int int64_t

    auto solve = [&]() {
        int n, m, k;
        std::cin >> n >> m >> k;

        auto check = [&](int mid) {
            int lef = 0;
            if (mid - (k - 1) >= 1) {
                lef = 1LL * (mid - (k - 1) + mid) * k / 2;
            } else {
                lef = 1LL * (1 + mid) * mid / 2 + (k - mid);
            }
            int rig = 0;
            if (mid - (n - k) >= 1) {
                rig = 1LL * (mid - (n - k) + mid) * (n - k + 1) / 2;
            } else {
                rig = 1LL * (1 + mid) * mid / 2 + (n - k - (mid - 1));
            }
            int res = lef + rig - mid;
            return res <= m and res > 0;
        };

        int lo = 1, hi = 1E18;
        while (lo <= hi) {
            int mid = lo + hi >> 1;
            if (check(mid)) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        std::cout << lo - 1 << "\n";

    };

    int t = 1;
    //std::cin>>t;
    while (t--) {
        solve();
    }

    return 0;
}

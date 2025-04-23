struct SA {
    int n;
    std::vector<int>sa, rk, lc;
    SA() = default;
    SA(const std::string& s) {
        n = s.size();
        int m = 128;
        // pay attention to the size
        rk.assign(2 * n + 1, 0);
        sa.assign(2 * n + 1, 0);
        std::vector<int>cnt(m + 1, 0);
        for (int i = 1; i <= n; i += 1) {
            cnt[rk[i] = s[i - 1]] += 1;
        }
        for (int i = 1; i <= m; i += 1) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = n; i >= 1; i -= 1) {
            sa[cnt[rk[i]]--] = i;
        }
        std::vector<int>ord(n + 1);
        for (int w = 1, p = 0; p != n; w <<= 1, m = p) {
            int cur = 0;
            for (int i = n - w + 1; i <= n; i += 1) {
                ord[++cur] = i;
            }
            for (int i = 1; i <= n; i += 1) {
                if (sa[i] > w) {
                    ord[++cur] = sa[i] - w;
                }
            }
            cnt.assign(m + 1, 0);
            for (int i = 1; i <= n; i += 1) {
                cnt[rk[i]] += 1;
            }
            for (int i = 1; i <= m; i += 1) {
                cnt[i] += cnt[i - 1];
            }
            for (int i = n; i >= 1; i -= 1) {
                sa[cnt[rk[ord[i]]]--] = ord[i];
            }
            p = 0;
            auto ork = rk;
            for (int i = 1; i <= n; i += 1) {
                if (ork[sa[i]] == ork[sa[i - 1]] and ork[sa[i] + w] == ork[sa[i - 1] + w]) {
                    rk[sa[i]] = p;
                } else {
                    rk[sa[i]] = ++p;
                }
            }
        }
        lc.assign(n + 1, 0);
        for (int i = 1, k = 0; i <= n; i += 1) {
            if (rk[i] == 1) {
                continue;
            }
            if (k) {
                k -= 1;
            }
            while (s[i + k - 1] == s[sa[rk[i] - 1] + k - 1]) {
                k += 1;
            }
            lc[rk[i]] = k;
        }
    }

    std::vector<std::vector<int>>rmq;
    void work() {
        int logn = std::__lg(n);
        rmq.assign(logn + 1, std::vector<int>(n + 1));
        std::copy(lc.begin(), lc.end(), rmq[0].begin());
        for (int j = 1; j <= logn; j += 1) {
            for (int i = 1; i + (1 << (j - 1)) - 1 <= n; i += 1) {
                rmq[j][i] = std::min(rmq[j - 1][i], rmq[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    constexpr int range(int l, int r) {
        int k = r - l + 1;
        k = std::__lg(k);
        return std::min(rmq[k][l], rmq[k][r - (1 << k) + 1]);
    }

    constexpr int lcp(int i, int j) {
        if (i < 1 || i > n || j < 1 || j > n) {
            return 0;
        }
        int u = rk[i], v = rk[j];
        if (u == v) {
            return n - sa[u] + 1;
        }
        if (u > v) {
            std::swap(u, v);
        }
        return range(u + 1, v);
    }
};
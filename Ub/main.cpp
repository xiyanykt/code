auto findFirst = [&](std::vector<int> d, int x) {
    auto dfs = [&](auto &&self, int p, int l, int r, std::vector<int> d) {
        int sum = 0;
        for (int c: d) {
            sum += ::t[c].cnt;
        }
        if (sum == r - l + 1) {
            return l;
        }
        if (l == r) {
            return r + 1;
        }
        int mid = (l + r) >> 1;
        if (x <= mid) {
            return self(self, p << 1, l, mid, lsh(d));
        } else {
            int res = self(self, p << 1 | 1, mid + 1, r, rsh(d));
            return res == mid + 1 ? self(self, p << 1, l, mid, lsh(d)) : res;
        }
    };
    return dfs(dfs, 1, 1, n, d);
};
auto findLast = [&](std::vector<int> d, int x) {
    auto dfs = [&](auto &&self, int p, int l, int r, std::vector<int> d) {
        int sum = 0;
        for (int c: d) {
            sum += ::t[c].cnt;
        }
        if (sum == r - l + 1) {
            return r;
        }
        if (l == r) {
            return l - 1;
        }
        int mid = (l + r) >> 1;
        if (mid + 1 <= x) {
            return self(self, p << 1 | 1, mid + 1, r, rsh(d));
        } else {
            int res = self(self, p << 1, l, mid, lsh(d));
            return res == mid ? self(self, p << 1 | 1, mid + 1, r, rsh(d)) : res;
        }
    };
    return dfs(dfs, 1, 1, n, d);
};

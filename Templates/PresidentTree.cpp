struct PresidentTree {
    struct Info {
        int lsh = 0, rsh = 0;
        int cnt = 0;
        i64 sum = 0;
        friend Info operator+(const Info& a, const Info& b) {
            return { -1, -1, a.cnt + b.cnt, a.sum + b.sum};
        }
    };

    int tot;
    std::vector<Info>t;
    PresidentTree(int KN) {
        tot = 0;
        t.resize((KN << 5) + 1);
    }

    void add(int& now, int pre, int L, int R, int x, int v = 1) {
        t[now = ++tot] = t[pre];
        t[now].cnt += v;
        t[now].sum += x;
        if (L == R) {
            return;
        }
        int mid = (L + R) >> 1;
        if (x <= mid) {
            add(t[now].lsh, t[pre].lsh, L, mid, x, v);
        } else {
            add(t[now].rsh, t[pre].rsh, mid + 1, R, x, v);
        }
    }

    int getKthMin(int l, int r, int L, int R, int k) {
        if (t[r].cnt - t[l].cnt < k) {
            return -1;
        }
        if (L == R) {
            return L;
        }
        int mid = (L + R) >> 1;
        int all = t[t[r].lsh].cnt - t[t[l].lsh].cnt;
        if (k <= all) {
            return getKthMin(t[l].lsh, t[r].lsh, L, mid, k);
        } else {
            return getKthMin(t[l].rsh, t[r].rsh, mid + 1, R, k - all);
        }
    }

    int getKthMax(int l, int r, int L, int R, int k) {
        if (t[r].cnt - t[l].cnt < k) {
            return -1;
        }
        if (L == R) {
            return R;
        }
        int mid = (L + R) >> 1;
        int all = t[t[r].rsh].cnt - t[t[l].rsh].cnt;
        if (k <= all) {
            return getKthMax(t[l].rsh, t[r].rsh, mid + 1, R, k);
        } else {
            return getKthMax(t[l].lsh, t[r].lsh, L, mid, k - all);
        }
    }

    Info getRange(int l, int r, int L, int R, int x, int y) {
        if (L > y or R < x) {
            return Info();
        }
        if (x <= L and R <= y) {
            return Info(-1, -1, t[r].cnt - t[l].cnt, t[r].sum - t[l].sum);
        }
        int mid = (L + R) >> 1;
        return getRange(t[l].lsh, t[r].lsh, L, mid, x, y) + getRange(t[l].rsh, t[r].rsh, mid + 1, R, x, y);
    }
};
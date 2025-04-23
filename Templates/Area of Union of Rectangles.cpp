template<class T = i64>
struct SegmentTree {
    int n;
    std::vector<T>info;
    std::vector<T>tag;
    std::vector<T>X;

    SegmentTree(const auto & xs) {
        X = xs;
        this->n = (int)xs.size() - 2;
        info.assign(8 * n, T());
        tag.assign(8 * n, T());
    }

    void pull(int p, int l, int r) {
        if (tag[p] != 0) {
            info[p] = X[r + 1] - X[l];
        } else {
            info[p] = info[p << 1 | 1] + info[p << 1];
        }
    }

    void update(int p, int l, int r, int L, int R, const T& val) {
        if (X[r + 1] <= L or X[l] >= R) {
            return;
        }
        if (L <= X[l] and X[r + 1] <= R) {
            tag[p] += val;
            pull(p, l, r);
            return;
        }
        int mid = l + r >> 1;
        update(p << 1, l, mid, L, R, val);
        update(p << 1 | 1, mid + 1, r, L, R, val);
        pull(p, l, r);
    }
    void update(int l, int r, const T& val) {
        update(1, 1, n, l, r, val);
    }

    T Query() {
        return info[1];
    }
};

struct Node {
    i64 y, l, r;
    int type;
    Node(i64 y, i64 l, i64 r, int type): y(y), l(l), r(r), type(type) {}

    friend bool operator<(const Node& lsh, const Node& rsh) {
        return lsh.y < rsh.y;
    }
};

i64 getArea(const auto & ret) {
    std::vector<Node>e;
    std::vector<i64>xs{0};
    for (const auto &[x1, y1, x2, y2] : ret) {
        e.push_back({y1, x1, x2, 1});
        e.push_back({y2, x1, x2, -1});
        xs.push_back(x1);
        xs.push_back(x2);
    }
    std::sort(e.begin(), e.end());
    std::sort(xs.begin() + 1, xs.end());

    xs.erase(std::unique(xs.begin() + 1, xs.end()), xs.end());
    SegmentTree seg(xs);

    i64 res = 0;
    for (int i = 0; i + 1 < (int)e.size(); i += 1) {
        seg.update(e[i].l, e[i].r, e[i].type);
        res += seg.Query() * (e[i + 1].y - e[i].y);
    }
    return res;
}

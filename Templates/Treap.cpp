template <class T>
struct Treap {
    std::mt19937 rng;
    struct Node {
        int lsh = 0, rsh = 0;
        T val = T();
        int key = 0, siz = 0, rev = 0;
    };

    int root, t1, t2, t3;
    std::vector<Node>info;
    Treap() : info(1), rng(220725) , root(0), t1(0), t2(0), t3(0) {}

    int newNode(const T& val) {
        info.emplace_back(0, 0, val, int(rng()), 1, 0);
        return info.size() - 1;
    }

    void push(int p) {
        info[p].siz = info[info[p].lsh].siz + info[info[p].rsh].siz + 1;
    }

    void pull(int p) {
        if (info[p].rev) {
            std::swap(info[p].lsh, info[p].rsh);
            if (info[p].lsh)info[info[p].lsh].rev ^= 1;
            if (info[p].rsh)info[info[p].rsh].rev ^= 1;
            info[p].rev = 0;
        }
    }

    void split_by_rank(int u, int k, int& x, int & y) {
        if (not u)return x = y = 0, void();
        pull(u);
        int cur = info[info[u].lsh].siz + 1;
        if (cur == k) {
            x = u, y = info[u].rsh;
            info[u].rsh = 0;
        } else if (cur > k) {
            y = u;
            split_by_rank(info[u].lsh, k, x, info[u].lsh);
        } else {
            x = u;
            split_by_rank(info[u].rsh, k - cur, info[u].rsh, y);
        }
        push(u);
    }

    void split_by_val(int u, const T& val, int& x, int& y) {
        if (not u)return x = y = 0, void();
        if (info[u].val > val) {
            y = u;
            split_by_val(info[u].lsh, val, x, info[u].lsh);
        } else {
            x = u;
            split_by_val(info[u].rsh, val, info[u].rsh, y);
        }
        push(u);
    }

    int merge(int x, int y) {
        if ((not x) or (not y))return x + y;
        pull(x), pull(y);
        if (info[x].key > info[y].key) {
            info[x].rsh = merge(info[x].rsh, y);
            push(x);
            return x;
        } else {
            info[y].lsh = merge(x, info[y].lsh);
            push(y);
            return y;
        }
    }

    void insert_rank(int x, const T& val) {
        split_by_rank(root, x - 1, t1, t2);
        root = merge(merge(t1, newNode(val)), t2);
    }

    void insert_val(const T& val) {
        split_by_val(root, val, t1, t2);
        root = merge(merge(t1, newNode(val)), t2);
    }

    void erase_rank(int x) {
        split_by_rank(root, x - 1, t1, t2);
        split_by_rank(t2, x, t2, t3);
        root = merge(t1, t3);
    }

    void erase_val(const T& val) {
        split_by_val(root, val, t1, t2);
        split_by_val(t1, val - 1, t1, t3);
        t3 = merge(info[t3].lsh, info[t3].rsh);
        root = merge(merge(t1, t3), t2);
    }

    int begin(int u) {
        return info[u].lsh == 0 ? u : begin(info[u].lsh);
    }

    int end(int u) {
        return info[u].rsh == u ? 0 : end(info[u].rsh);
    }

    void flip(int l, int r) {
        split_by_rank(root, l - 1, t1, t2);
        split_by_rank(t2, r - l + 1, t2, t3);
        info[t2].rev ^= 1;
        root = merge(merge(t1, t2), t3);
    }

    int erase_begin(int u) {
        if (not info[u].lsh)return info[u].rsh;
        info[u].lsh = erase_begin(info[u].lsh);
        push(u);
        return u;
    }

    int erase_end(int u) {
        if (not info[u].rsh)return info[u].lsh;
        info[u].rsh = erase_end(info[u].rsh);
        push(u);
        return u;
    }

    int order_of_key(const T& val) {
        split_by_val(root, val - 1, t1, t2);
        int res = info[t1].siz + 1;
        root = merge(t1, t2);
        return res;
    }

    T find_by_order(int k) {
        int u = root;
        while (u) {
            int cur = info[info[u].lsh].siz + 1;
            if (cur == k)break;
            if (cur > k) {
                u = info[u].lsh;
            } else {
                k -= cur;
                u = info[u].rsh;
            }
        }
        return info[u].val;
    }

    T findPref(const T& x) {
        split_by_val(root, x - 1, t1, t2);
        int u = t1;
        while (info[u].rsh) {
            u = info[u].rsh;
        }
        root = merge(t1, t2);
        return info[u].val;
    }

    T findSurf(const T& x) {
        split_by_val(root, x, t1, t2);
        int u = t2;
        while (info[u].lsh) {
            u = info[u].lsh;
        }
        root = merge(t1, t2);
        return info[u].val;
    }

    void travel(int p) {
        pull(p);
        if (info[p].lsh)travel(info[p].lsh);
        std::cout << info[p].val << ' ';
        if (info[p].rsh)travel(info[p].rsh);
    }
};
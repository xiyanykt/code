struct LinkCutTree {
    struct Node {
        int rev = 0;
        int siz = 1;
        int par = 0;
        std::array<int, 2> ch{};
    };

    std::vector<Node> t;
    LinkCutTree(const int& n) {
        t.assign(n + 1, Node());
        t[0].siz = 0;
    }

    void pull(int p) {
        t[p].siz = t[t[p].ch[0]].siz + t[t[p].ch[1]].siz + 1;
    }

    void flip(int p) {
        std::swap(t[p].ch[0], t[p].ch[1]);
        t[p].rev ^= 1;
    }

    void push(int p) {
        if (t[p].rev) {
            if (t[p].ch[0])flip(t[p].ch[0]);
            if (t[p].ch[1])flip(t[p].ch[1]);
            t[p].rev = 0;
        }
    }

    bool isroot(int p) {
        return (p != t[t[p].par].ch[0] and p != t[t[p].par].ch[1]);
    }

    int pos(int p) {
        return t[t[p].par].ch[1] == p;
    }

    void rotate(int p) {
        int x = t[p].par, y = t[t[p].par].par, k = pos(p), r = t[p].ch[!k];
        if (not isroot(x)) {
            t[y].ch[pos(x)] = p;
        }
        t[p].ch[!k] = x, t[x].ch[k] = r;
        if (r) {
            t[r].par = x;
        }
        t[x].par = p, t[p].par = y;
        pull(x);
        pull(p);
    }

    void pushAll(int p) {
        if (not isroot(p)) {
            pushAll(t[p].par);
        }
        push(p);
    }

    void splay(int p) {
        pushAll(p);
        while (not isroot(p)) {
            if (not isroot(t[p].par)) {
                rotate((pos(t[p].par) == pos(p)) ? t[p].par : p);
            }
            rotate(p);
        }
        pull(p);
    }

    int access(int p) {
        int q = 0;
        for (; p; q = p, p = t[p].par) {
            splay(p);
            t[p].ch[1] = q;
            pull(p);
        }
        return q;
    }

    void makeroot(int p) {
        access(p);
        splay(p);
        flip(p);
    }

    int findroot(int p) {
        access(p);
        splay(p);
        while (t[p].ch[0]) {
            push(p);
            p = t[p].ch[0];
        }
        splay(p);
        return p;
    }

    void link(int u, int v) {
        makeroot(u);
        if (findroot(v) != u) {
            t[u].par = v;
        }
    }

    void cut(int u, int v) {
        makeroot(u);
        if (findroot(v) == u and t[v].par == u) {
            t[v].par = t[u].ch[1] = 0;
            pull(u);
        }
    }
};

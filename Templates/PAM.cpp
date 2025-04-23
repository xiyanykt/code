struct PAM {
    static constexpr int ALPHABET = 26;
    static constexpr char OFFSET = 'a';
    struct Node {
        int len;
        int cnt;
        int suffixlink;
        std::array<int, ALPHABET>next;
        Node(): len{}, cnt{}, suffixlink{}, next{} {}
    };

    int suff;
    std::vector<Node>t;
    std::string s;

    PAM() {
        t.assign(2, Node());
        t[0].suffixlink = 1;
        t[1].suffixlink = 1;
        t[1].len = -1;
        suff = 0;
        s = "$";
    }

    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }

    int getfali(int u, int p) {
        while (p - t[u].len - 1 <= 0 or s[p - t[u].len - 1] != s[p]) {
            u = t[u].suffixlink;
        }
        return u;
    }

    void add(const char& c, int p) {
        s += c;
        int par = getfali(suff, p);
        if (not t[par].next[c - OFFSET]) {
            int cur = newNode();
            t[cur].suffixlink = t[getfali(t[par].suffixlink, p)].next[c - OFFSET];
            t[par].next[c - OFFSET] = cur;
            t[cur].len = t[par].len + 2;
            t[cur].cnt = t[t[cur].suffixlink].cnt + 1;
        }
        suff = t[par].next[c - OFFSET];
    }

    int size() {
        return t.size();
    }

    int next(int p, const char& c) {
        return t[p].next[c - OFFSET];
    }

    int link(int p) {
        return t[p].suffixlink;
    }

    int len(int p) {
        return t[p].len;
    }

    int cnt(int p) {
        return t[p].cnt;
    }

    std::vector<std::vector<int>>work() {
        std::vector adj(size(), std::vector<int>());
        for (int i = 2; i < size(); i += 1) {
            adj[link(i)].push_back(i);
        }
        return adj;
    }
};
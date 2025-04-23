struct AhoCorasick {
    static constexpr int ALPHABET = 26;

    struct Node {
        int len;
        int link;
        std::array<int, ALPHABET>next;
        Node(): len{0}, link{0}, next{} {}
    };
    std::vector<Node>t;

    AhoCorasick() {
        t.assign(2, {});
        t[0].next.fill(1);
        t[0].len = -1;
    }

    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }

    int add(const std::string& s) {
        int p = 1;
        for (const auto & x : s) {
            int c = x - 'a';
            if (t[p].next[c] == 0) {
                t[p].next[c] = newNode();
                t[t[p].next[c]].len = t[p].len + 1;
            }
            p = t[p].next[c];
        }
        return p;
    }

    void work() {
        std::queue<int>q;
        q.push(1);
        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            for (int i = 0; i < ALPHABET; i += 1) {
                if (t[u].next[i]) {
                    t[t[u].next[i]].link = t[t[u].link].next[i];
                    q.push(t[u].next[i]);
                } else {
                    t[u].next[i] = t[t[u].link].next[i];
                }
            }
        }
    }

    int next(int p, int c) {
        return t[p].next[c];
    }

    int len(int p) {
        return t[p].len;
    }

    int link(int p) {
        return t[p].link;
    }

    int size() {
        return t.size();
    }
};
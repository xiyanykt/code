struct LowestCommonAncestor {
    int n, low, cnt;
    std::vector<int>seq, dfn, lst, ord;
    std::vector<std::vector<int>>adj, jump;

    LowestCommonAncestor(const int& n) {
        this->n = n;
        low = cnt = 0;
        adj.assign(n + 1, {});
        seq.assign(n + 1, 0);
        dfn.assign(n + 1, 0);
        lst.assign(n + 1, 0);
        ord.assign(2 * n + 1, 0);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u, int par) {
        dfn[u] = ++low;
        seq[low] = u;
        ord[++cnt] = u;
        lst[u] = cnt;
        for (const auto & v : adj[u]) {
            if (v == par) {
                continue;
            }
            dfs(v, u);
            ord[++cnt] = u;
            lst[u] = cnt;
        }
    }

    void work() {
        dfs(1, 0);
        int lgn = std::__lg(cnt);
        jump.assign(lgn + 2, std::vector<int>(cnt + 1));
        for (int i = 1; i <= cnt; i += 1) {
            jump[0][i] = dfn[ord[i]];
        }
        for (int j = 1; j <= lgn + 1; j += 1) {
            for (int i = 1; i + (1 << j) - 1 <= cnt; i += 1) {
                jump[j][i] = std::min(jump[j - 1][i], jump[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    constexpr int operator()(int l, int r)const {
        l = lst[l], r = lst[r];
        if (l > r) {
            std::swap(l, r);
        }
        int k = std::__lg(r - l + 1);
        return seq[std::min(jump[k][l], jump[k][r - (1 << k) + 1])];
    }
};

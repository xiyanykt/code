struct TwoSat {
    int n;
    std::vector<std::vector<int>>adj;
    std::vector<bool>res;

    TwoSat() {

    }

    TwoSat(const int & n): n(n), adj(2 * n + 2), res(n + 1) {}

    void addClause(int u, bool f, int v, bool g) {
        // 本质上, 点 u 对应条件 f, 点 v 对应条件 g, 在Satisfiable True的情况下两个中的一个必定成立
        adj[2 * u + !f].push_back(2 * v + g);
        adj[2 * v + !g].push_back(2 * u + f);
    }

    bool Satisfiable() {
        int cur = 0, cnt = 0;
        std::vector<int>stk, bel(2 * n + 2, -1), low(2 * n + 2, -1), dfn(2 * n + 2, -1);
        auto dfs = [&](auto && dfs, int x) ->void {
            stk.push_back(x);
            low[x] = dfn[x] = ++cur;
            for (const auto & y : adj[x]) {
                if (dfn[y] == -1) {
                    dfs(dfs, y);
                    low[x] = std::min(low[x], low[y]);
                } else if(bel[y] == -1){
                    low[x] = std::min(low[x], dfn[y]);
                }
            }
            if (dfn[x] == low[x]) {
                cnt += 1;
                int y;
                do {
                    y = stk.back();
                    stk.pop_back();
                    bel[y] = cnt;
                } while (y != x);
            }
        };

        for (int u = 1; u <= 2 * n + 1; u += 1) {
            if (dfn[u] == -1) {
                dfs(dfs, u);
            }
        }

        for (int u = 1; u <= n; u += 1) {
            if (bel[2 * u] == bel[2 * u + 1]) {
                return false;
            }
            res[u] = bel[2 * u] > bel[2 * u + 1];
        }

        return true;
    }

    std::vector<bool> answer() {
        return res;
    }
};
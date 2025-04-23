constexpr int inf = 1E9;
template <class T>
struct MaxFlow {
    struct edge {
        int to;
        T cap;
        edge(const int& to, const T& cap): to(to), cap(cap) {}
    };
    int n;
    std::vector<edge>e;
    std::vector<std::vector<int>>adj;
    std::vector<T>cur, h;

    MaxFlow() {}
    MaxFlow(int n): n{n}, e{}, adj(n), cur(n), h(n) {}
    
    bool bfs(int s, int t) {
        h.assign(n, -1);
        std::queue<int>Q;
        h[s] = 0;
        Q.push(s);
        while (not Q.empty()) {
            auto u = Q.front();
            Q.pop();
            for (const auto & i : adj[u]) {
                const auto & [to, cap] = e[i];
                if (cap > 0 and h[to] == -1) {
                    h[to] = h[u] + 1;
                    if (to == t) {
                        return true;
                    }
                    Q.push(to);
                }
            }
        }
        return false;
    }

    T dfs(int u, int t, T f) {
        if (u == t) {
            return f;
        }
        T r = f;
        for (int& i = cur[u]; i < (int)adj[u].size(); i += 1) {
            const int j = adj[u][i];
            auto [v, cap] = e[j];
            if (cap > 0 and h[v] == h[u] + 1) {
                auto a = dfs(v, t, std::min(r, cap));
                e[j].cap -= a;
                e[j ^ 1].cap += a;
                r -= a;
                if (r == 0) {
                    return f;
                }
            }
        }
        return f - r;
    }

    void addEdge(int u, int v, T c) {
        adj[u].push_back(e.size());
        e.emplace_back(v, c);
        adj[v].push_back(e.size());
        e.emplace_back(u, 0);
    }

    T flow(int s, int t) {
        T res = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            res += dfs(s, t, std::numeric_limits<T>::max());
        }
        return res;
    }

    std::vector<bool> minCut() {
        std::vector<bool> c(n);
        for (int i = 0; i < n; i++) {
            c[i] = (h[i] != -1);
        }
        return c;
    }

    struct Edge {
        int from;
        int to;
        T cap;
        T flow;
    };

    std::vector<Edge>edges() {
        std::vector<Edge>rec;
        for (int i = 0; i < e.size(); i += 2) {
            rec.push_back({.from = e[i + 1].to, .to = e[i].to, .cap = e[i].cap + e[i + 1].cap, .flow = e[i + 1].cap});
        }
        return rec;
    }
};
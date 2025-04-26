template<class T>
struct MinCostFlow {
    struct edge {
        int to;
        T cap;
        T flow;
        edge(int to, T cap, T flow): to{to}, cap{cap}, flow{flow} {}
    };

    int n;
    std::vector<edge>e;
    std::vector<std::vector<int>>adj;
    std::vector<T>h, dis;
    std::vector<int>pre;

    bool dijkstra(int s, int t) {
        pre.assign(n, -1);
        dis.assign(n, std::numeric_limits<T>::max());
        std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>, std::greater<>>q;
        q.push({dis[s] = 0, s});
        while (!q.empty()) {
            auto [d, u] = q.top();
            q.pop();
            if (dis[u] != d) {
                continue;
            }
            for (int i : adj[u]) {
                auto [v, cap, cost] = e[i];
                if (cap > 0 && dis[v] > d + h[u] - h[v] + cost) {
                    pre[v] = i;
                    q.push({dis[v] = d + h[u] - h[v] + cost, v});
                }
            }
        }
        return dis[t] != std::numeric_limits<T>::max();
    }

    MinCostFlow() {}
    MinCostFlow(int n): n{n}, e{}, adj(n) {}

    void addEdge(int u, int v, T cap, T cost) {
        adj[u].push_back(e.size());
        e.emplace_back(v, cap, cost);
        adj[v].push_back(e.size());
        e.emplace_back(u, 0, -cost);
    }

    std::pair<T, T> flow(int s, int t) {
        T flow = 0, cost = 0;
        h.assign(n, 0);
        while (dijkstra(s, t)) {
            for (int i = 0; i < n; i += 1) {
                h[i] += dis[i];
            }
            T aug = std::numeric_limits<T>::max();
            for (int i = t; i != s; i = e[pre[i] ^ 1].to) {
                aug = std::min(aug, e[pre[i]].cap);
            }
            for (int i = t; i != s; i = e[pre[i] ^ 1].to) {
                e[pre[i]].cap -= aug;
                e[pre[i] ^ 1].cap += aug;
            }
            flow += aug;
            cost += aug * h[t];
        }
        return std::pair(flow, cost);
    }

    struct Edge {
        int from;
        int to;
        T cap;
        T cost;
        T flow;
    };
    std::vector<Edge> edges() {
        std::vector<Edge> a;
        for (int i = 0; i < e.size(); i += 2) {
            Edge x;
            x.from = e[i + 1].to;
            x.to = e[i].to;
            x.cap = e[i].cap + e[i + 1].cap;
            x.cost = e[i].cost;
            x.flow = e[i + 1].cap;
            a.push_back(x);
        }
        return a;
    }
};
#include<bits/stdc++.h>

using i64 = int64_t;

#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) (void)42
#endif

struct Graph {
    int n;
    std::vector<std::vector<int>>adj;
    std::vector<i64>ans;
    std::vector<int>siz, son, par, l, r, low;
    int dfn;

    Graph() {}
    Graph(int n) {
        this->n = n;
        adj.assign(n + 1, std::vector<int>());
        ans.assign(n + 1, 0);
        siz.assign(n + 1, 0), son.assign(n + 1, 0), par.assign(n + 1, 0), l.assign(n + 1, 0), r.assign(n + 1, 0), low.assign(n + 1, 0);
        dfn = 0;
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void work() {
        auto dfs = [&](auto && self, int u)->void{
            siz[u] += 1;
            l[u] = ++dfn;
            low[dfn] = u;
            for (const auto &v : adj[u]) {
                if (v == par[u]) {
                    continue;
                }
                par[v] = u;
                self(self, v);
                siz[u] += siz[v];
                if (siz[v] > siz[son[u]]) {
                    son[u] = v;
                }
            }
            r[u] = dfn;
        };
        dfs(dfs, 1);
    }

    // template<typename T>
    auto getRes(const auto& c) {
        std::vector<int>cnt(n + 1);
        std::map<int, i64>clz;

        auto add = [&](int p) {
            clz[cnt[c[p]]] -= c[p];
            cnt[c[p]] += 1;
            clz[cnt[c[p]]] += c[p];
        };
        auto del = [&](int p) {
            clz[cnt[c[p]]] -= c[p];
            if (not clz[cnt[c[p]]]) {
                clz.erase(cnt[c[p]]);
            }
            cnt[c[p]] -= 1;
            clz[cnt[c[p]]] += c[p];
        };
        auto Ans = [&]() {
            return (clz.rbegin()->second);
        };

        auto dfs = [&](auto && self, int u, int top = 0)->void {
            for (const auto & v : adj[u]) {
                if (v == par[u] or v == son[u]) {
                    continue;
                }
                self(self, v);
            }
            if (son[u]) {
                self(self, son[u], 1);
            }
            for (const auto &v : adj[u]) {
                if (v == par[u] or v == son[u]) {
                    continue;
                }
                for (int j = l[v]; j <= r[v]; j += 1) {
                    add(low[j]);
                }
            }
            add(u);
            ans[u] = Ans();
            if (not top) {
                for (int j = l[u]; j <= r[u]; j += 1) {
                    del(low[j]);
                }
            }
        };
        dfs(dfs, 1);
        return ans;
    }
};

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;

    Graph g(n);
    std::vector<int>c(n + 1);
    for (int i = 1; i <= n; i += 1) {
        std::cin >> c[i];
    }

    for (int i = 1; i <= n - 1; i += 1) {
        int u, v;
        std::cin >> u >> v;
        g.addEdge(u, v);
    }

    g.work();
    auto res = g.getRes(c);

    for (int i = 1; i <= n; i += 1) {
        std::cout << res[i] << " \n"[i == n];
    }
    return 0;
}
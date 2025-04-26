#include<bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f64 = long double;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

#ifndef ONLINE_JUDGE
#include "algo/debug.hpp"
#else
#define debug(...) (void)13
#endif

template<class T>
constexpr bool chmax (T& x, T y) {
    if (y > x) {
        x = y;
        return true;
    }
    return false;
}

template<class T>
constexpr bool chmin (T& x, T y) {
    if (y < x) {
        x = y;
        return true;
    }
    return false;
}

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

constexpr int Kn = 1E5;
int minp[Kn + 1];
std::vector<int>primes;

void sieve(int n) {
    for (int x = 2; x <= n; x += 1) {
        if (minp[x] == 0) {
            minp[x] = x;
            primes.push_back(x);
        }
        for (const auto & p : primes) {
            if (p * x > n) {
                break;
            }
            minp[p * x] = p;
            if (p == minp[x]) {
                break;
            }
        }
    }
}

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    sieve(Kn);

    int n;
    std::cin >> n;

    std::vector<int>a(n + 1);
    for (int i = 1; i <= n; i += 1) {
        std::cin >> a[i];
    }

    auto work = [&](int x) {
        int cnt = 0;
        for (int p : primes) {
            if (p * p > x) {
                break;
            }
            while (x % p == 0) {
                cnt += 1;
                x /= p;
            }
        }
        if (x != 1) {
            cnt += 1;
        }
        return cnt;
    };

    int ans = 0;
    std::vector<int>v;
    std::vector<std::vector<std::pair<int, int>>>adj(n + 1);
    for (int i = 1; i <= n; i += 1) {
        std::vector<std::pair<int, int>>f;
        for (int d = 1; d * d <= a[i]; d += 1) {
            if (a[i] % d == 0) {
                int c = work(d);
                f.push_back({c, d});
                if (a[i] != d * d) {
                    int c = work(a[i] / d);
                    f.push_back({c, a[i] / d});
                }
            }
        }
        ans += work(a[i]);
        std::sort(f.begin(), f.end());
        for (int j = 0; j < std::min(n, int(f.size())); j += 1) {
            auto [c, d] = f[j];
            v.push_back(d);
            adj[i].push_back({d, c});
        }
    }

    std::sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(), v.end()), v.end());

    int s = 0, t = n + v.size() + 1;
    constexpr int inf = 1E9;
    MinCostFlow<int>mcf(t + 1);
    for (int i = 1; i <= n; i += 1) {
        mcf.addEdge(s, i, 1, 0);
        for (auto [d, c] : adj[i]) {
            int j = std::lower_bound(v.begin(), v.end(), d) - v.begin();
            mcf.addEdge(i, n + j + 1, 1, 0);
        }
    }
    for (int i = 0; i < v.size(); i += 1) {
        mcf.addEdge(n + i + 1, t, 1, work(v[i]));
    }

    auto [flow, cost] = mcf.flow(s, t);
    std::cout << ans - cost << '\n';
    return 0;
}
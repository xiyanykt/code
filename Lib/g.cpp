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

struct HLD {
    int n;
    std::vector<std::vector<int>>adj;
    std::vector<int>dfn, siz, par, son, top, dep, seq;
    int cur;

    HLD() {}
    HLD(int n): n{n}, adj(n + 1), dfn(n + 1), par(n + 1), son(n + 1), siz(n + 1), dep(n + 1), top(n + 1), seq(n + 1), cur{0} {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u) {
        siz[u] += 1;
        dep[u] = dep[par[u]] + 1;
        for (const auto & v : adj[u]) {
            if (v == par[u]) {
                continue;
            }
            par[v] = u;
            dfs(v);
            siz[u] += siz[v];
            if (siz[v] > siz[son[u]]) {
                son[u] = v;
            }
        }
    }
    void dfs(int u, int h) {
        dfn[u] = ++cur;
        seq[cur] = u;
        top[u] = h;
        if (son[u]) {
            dfs(son[u], h);
        }
        for (const auto & v : adj[u]) {
            if (v == son[u] or v == par[u]) {
                continue;
            }
            dfs(v, v);
        }
    }

    void work(int s = 1) {
        dfs(s);
        dfs(s, s);
    }

    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) {
                std::swap(u, v);
            }
            u = par[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }

    int lca(int u, int v, int root) {
        return lca(u, v) ^ lca(u, root) ^ lca(v, root);
    }

    int dist(int u, int v) {
        return (dep[u] + dep[v] - 2 * dep[lca(u, v)]);
    }

    int jump(int u, int k) {
        if (dep[u] <= k) {
            return -1;
        }
        int d = dep[u] - k;
        while (dep[top[u]] > d) {
            u = par[top[u]];
        }
        return seq[dfn[u] + d - dep[u]];
    }

    int left(int u) {
        return dfn[u];
    }

    int right(int u) {
        return dfn[u] + siz[u] - 1;
    }

    bool isAncestor(int u, int v) {
        return dfn[u] <= dfn[v] and dfn[v] < dfn[u] + siz[u];
    }
};

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

template<typename T>
struct Fenwick {
	int n;
	std::vector<T>a;
    Fenwick() = default;
    Fenwick(int n): n{n}, a(n + 1, T{}) {}

	void add(int p, const T& x) {
		if (p >= 1 && p <= n) {
			for (int i = p; i <= n; i += i & -i) {
				a[i] += x;
			}
		}
	}

	T sum(int p) {
		T ans = T();
		if (p >= 1 && p <= n) {
			for (int i = p; i > 0; i -= i & -i) {
				ans += a[i];
			}
		}
		return ans;
	}

	T rangeQuery(int l, int r) {
		return sum(r) - sum(l - 1);
	}

	int select(int k) {
		int x = 0;
		T cur = T();
		for (int i = std::__lg(n); ~i; i -= 1) {
			x += 1 << i;
			if (x >= n or cur + a[x] >= k) {
				x -= 1 << i;
			} else {
				cur = cur + a[x];
			}
		}
		return x + 1;
	}
};

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    AhoCorasick ac;
    int m = 0;
    std::vector<int>end(n + 1);
    std::vector<std::string>s(n + 1);
    for (int i = 1; i <= n; i += 1) {
        std::cin >> s[i];
        m += s[i].length();
        end[i] = ac.add(s[i]);
    }
    ac.work();

    HLD hld(ac.size());
    for (int i = 2; i < ac.size(); i += 1) {
        hld.addEdge(ac.link(i), i);
    }
    hld.work();

    // int b = std::sqrt(m);
    int b = m / std::sqrt(q * std::__lg(m));
    std::vector<i64>ans(q + 1);
    std::vector<std::vector<std::pair<int, int>>>qry1(n + 1);
    std::vector<std::vector<std::array<int, 3>>>qry2(n + 1);
    for (int i = 1; i <= q; i += 1) {
        int l, r, k;
        std::cin >> l >> r >> k;
        if (int(s[k].length()) <= b) {
            if (l - 1 >= 1) {
                qry1[l - 1].push_back({~k, i});
            }
            qry1[r].push_back({k, i});
        } else {
            qry2[k].push_back({l, r, i});
        }
    }
    // m / b * n * log(m)
    for (int k = 1; k <= n; k += 1) {
        if (!qry2[k].empty()) {
            std::vector<i64>sum(n + 1);
            Fenwick<i64>fen(ac.size() + 1);

            int p = 1;
            for (char c : s[k]) {
                p = ac.next(p, c - 'a');
                fen.add(hld.left(p), 1);
            }

            for (int j = 1; j <= n; j += 1) {
                sum[j] += sum[j - 1];
                sum[j] += fen.rangeQuery(hld.left(end[j]), hld.right(end[j]));
            }

            for (auto & [l, r, i] : qry2[k]) {
                ans[i] = sum[r] - sum[l - 1];
            }
        }
    }
    // n * log(m) * b
    Fenwick<i64>fen(ac.size() + 1);
    for (int i = 1; i <= n; i += 1) {
        fen.add(hld.left(end[i]), 1);
        fen.add(hld.right(end[i]) + 1, -1);

        for (auto & [k, e] : qry1[i]) {
            if (k >= 1) {
                int p = 1;
                for (char c : s[k]) {
                    p = ac.next(p, c - 'a');
                    ans[e] += fen.sum(hld.left(p));
                }
            } else {
                int p = 1;
                for (char c : s[~k]) {
                    p = ac.next(p, c - 'a');
                    ans[e] -= fen.sum(hld.left(p));
                }
            }
        }
    }

    for (int i = 1; i <= q; i += 1) {
        std::cout << ans[i] << '\n';
    }
    return 0;
}
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
#define debug(...) (void)42
#endif

template<class T>
constexpr bool chmax(T& x, T y) {
    if (y > x) {
        x = y;
        return true;
    }
    return false;
}

template<class T>
constexpr bool chmin(T& x, T y) {
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
    HLD(int n) {
        this->n = n;
        adj.assign(n + 1, std::vector<int>());
        dfn.resize(n + 1), par.resize(n + 1);
        son.resize(n + 1), siz.resize(n + 1);
        dep.resize(n + 1), top.resize(n + 1);
        seq.resize(n + 1);
        cur = 0;
    }

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

template<typename T>
struct Fenwick {
	int n;
	std::vector<T>a;

	Fenwick() {

	}
	
	Fenwick(int n) {
		this->n = n;
		a.assign(n + 1, T());
	}

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

    auto solve = [&]() {
        int n;
        std::cin >> n;

        HLD hld(n);
        for (int i = 1; i <= n - 1; i += 1) {
            int u, v;
            std::cin >> u >> v;
            hld.addEdge(u, v);
        }        
        hld.work();

        i64 res = 0;
        auto& adj = hld.adj;
        auto& par = hld.par, son = hld.son, dfn = hld.dfn, seq = hld.seq, dep = hld.dep;
        Fenwick<i64>f1(n);
        Fenwick<i64>f2(n);

        // 对于符合的情况来说 res = 2 * min(d[u], d[v]) - 2 * d[lca] - 1
        // 显然符合的情况一定跨越子树, 可以直接dsu on tree统计答案, 枚举lca, 然后枚举子树里面哪一个点分别作为max和min即可
        auto dfs = [&](this auto && dfs, int u, int top = 0) ->void {
            for (const auto & v : adj[u]) {
                if (v == son[u] || v == par[u]) {
                    continue;
                }
                dfs(v);
            }
            if (son[u]) {
                dfs(son[u], 1);
            }
            for (const auto & v : adj[u]) {
                if (v == par[u] || v == son[u]) {
                    continue;
                }
                for (int j = hld.left(v); j <= hld.right(v); j += 1) {
                    int x = seq[j];
                    auto c1 = f1.rangeQuery(1, dep[x]), c2 = f1.rangeQuery(dep[x] + 1, n);
                    auto s1 = f2.rangeQuery(1, dep[x]), s2 = f2.rangeQuery(dep[x] + 1, n);
                    res += c2 * (2 * dep[x] - 2 * dep[u] - 1);
                    res += 2 * s1 - c1 * 2 * dep[u] - c1;
                }
                for (int j = hld.left(v); j <= hld.right(v); j += 1) {
                    int x = seq[j];
                    f1.add(dep[x], 1);
                    f2.add(dep[x], dep[x]);
                }
            }
            f1.add(dep[u], 1);
            f2.add(dep[u], dep[u]);
            if (!top) {
                for (int j = hld.left(u); j <= hld.right(u); j += 1) {
                    int x = seq[j];
                    f1.add(dep[x], -1);
                    f2.add(dep[x], -dep[x]);
                }
            }
        };
        dfs(1);

        std::cout << res << '\n';
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
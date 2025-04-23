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

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int>a(n + 1);
    for (int i = 1; i <= n; i += 1) {
        std::cin >> a[i];
    }

    auto b = a;
    std::ranges::sort(b);
    b.erase(std::unique(b.begin() + 1, b.end()), b.end());

    for (int i = 1; i <= n; i += 1) {
        a[i] = std::lower_bound(b.begin() + 1, b.end(), a[i]) - b.begin();
    }

    std::vector<int>tot(n + 1);
    for (int i = 1; i <= n; i += 1) {
        tot[a[i]] += 1;
    }

    std::vector<std::vector<int>>adj(n + 1);
    for (int i = 1; i <= n - 1; i += 1) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    struct Node {
        Node* ch[2] {nullptr, nullptr};
        int cnt = 0;
        i64 sum = 0;
    };

    auto add = [&](auto && self, Node*& t, int l, int r, int x) ->void {
        if (t == nullptr) {
            t = new Node;
        }
        if(l == r) {
            t->cnt += 1;
            t->sum = 1LL * t->cnt * (tot[l] - t->cnt);
            return ; 
        }
        int mid = (l + r) >> 1;
        if (x <= mid) {
            self(self, t->ch[0], l, mid, x);
        } else {
            self(self, t->ch[1], mid + 1, r, x);
        }
        t->sum = (t->ch[0] != nullptr ? t->ch[0]->sum : 0LL) + (t->ch[1] != nullptr ? t->ch[1]->sum : 0LL);
    };

    auto merge = [&](auto && self, Node* a, Node* b, int l, int r, i64& res, int x) ->Node* {
        if (a == nullptr) {
            return b;
        }
        if (b == nullptr) {
            return a;
        }
        if (l == r) {
            if (l < x) {
                res += 1LL * a->cnt * b->cnt;
            }
            a->cnt += b->cnt;
            a->sum = 1LL * a->cnt * (tot[l] - a->cnt);
            return a;
        }
        int mid = (l + r) >> 1;
        a->ch[0] = self(self, a->ch[0], b->ch[0], l, mid, res, x);
        a->ch[1] = self(self, a->ch[1], b->ch[1], mid + 1, r, res, x);
        a->sum = (a->ch[0] != nullptr ? a->ch[0]->sum : 0LL) + (a->ch[1] != nullptr ? a->ch[1]->sum : 0LL);
        return a;
    };

    auto query = [&](auto&& self, Node*& t, int l, int r, int L, int R) {
        if (t == nullptr || l > R || r < L) {
            return 0LL;
        }
        if (L <= l && r <= R) {
            return t->sum;
        }
        int mid = (l + r) >> 1;
        return self(self, t->ch[0], l, mid, L, R) + self(self, t->ch[1], mid + 1, r, L, R);
    };

    i64 res = 0;
    std::vector<Node *>t(n + 1);
    auto dfs = [&](auto && self, int u, int p) ->void {
        add(add, t[u], 1, n, a[u]);
        for (const auto & v : adj[u]) {
            if (v == p) {
                continue;
            }
            self(self, v, u);
            t[u] = merge(merge, t[u], t[v], 1, n, res, a[u]);
        }
        if (a[u] > 1) {
            res += query(query, t[u], 1, n, 1, a[u] - 1);
        }
    };
    dfs(dfs, 1, 0);

    std::cout << res << '\n';
    return 0;
}
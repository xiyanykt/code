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

struct DSU {
	std::vector<int>par, siz;
	DSU() = default;
	
	DSU(int n): par(n + 1), siz(n + 1, 1) {
        std::iota(par.begin(), par.end(), 0);
    }

	int find(int x) {
		while (x != par[x]) {
			x = par[x] = par[par[x]];
		}
		return x;
	}

	bool same(int x, int y) {
		return find(x) == find(y);
	}

	bool merge(int x, int y) {
		x = find(x), y = find(y);
		if (x == y) {
			return false;
		}
		if (siz[x] < siz[y]) {
			std::swap(x, y);
		}
		siz[x] += siz[y];
		par[y] = x;
		return true;
	}

	int size(int x) {
		return siz[find(x)];
	}
};

static const u64 r = std::chrono::steady_clock::now().time_since_epoch().count();

u64 salt(u64 x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
}

u64 f(u64 x) {
    return salt(x + r);
}

void solve () {
    int n, m;
    std::cin >> n >> m;
    
    std::vector<int>deg(n + 1);
    std::vector<std::vector<int>>adj(n + 1);
    for (int i = 1; i <= m; i += 1) {
        int u, v;
        std::cin >> u >> v;
        deg[u] ++;
        deg[v] ++;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if (m == n - 1) {
        std::cout << "YES\n";
        return ;
    }

    if (m != n) {
        std::cout << "NO\n";
        return ;
    }

    std::vector<int>vis(n + 1);
    std::vector<std::vector<int>>e(n + 1);
    auto dfs1 = [&](auto && dfs1, int u) ->void {
        vis[u] = 1;
        for (int v : adj[u]) {
            if (vis[v]) {
                continue;
            }
            e[v].push_back(u);
            deg[v]--;
            if (deg[v] == 1) {
                dfs1(dfs1, v);
            }
        }
    };

    for (int u = 1; u <= n; u += 1) {
        if (!vis[u] && deg[u] == 1) {
            dfs1(dfs1, u);
        }
    }

    std::vector<int>cyc;
    auto dfs2 = [&](auto && dfs2, int u) ->void {
        vis[u] = 1;
        cyc.push_back(u);
        for (int v : adj[u]) {
            if (!vis[v]) {
                dfs2(dfs2, v);
            }
        }
    };

    for (int u = 1; u <= n; u += 1) {
        if (!vis[u]) {
            dfs2(dfs2, u);
        }
    }

    int c = cyc.size();
    std::vector<u64>h(n + 1);
    auto dfs = [&](auto && dfs, int u) ->void {
        h[u] = 1;  
        for (int v : e[u]) {
            dfs(dfs, v);
            h[u] += f(h[v]);
        }
    };
    for (int v : cyc) {
        dfs(dfs, v);
    }

    for (int i = 0; i < c; i += 1) {
        if (h[cyc[i]] != h[cyc[(i + 2) % c]]) {
            std::cout << "NO\n";
            return;
        }
    }

    std::cout << "YES\n";
}

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
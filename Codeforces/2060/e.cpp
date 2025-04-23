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

struct DSU {
	std::vector<int>par, siz;

	DSU() {

	}
	
	DSU(int n) {
		par.resize(n + 1);
		std::iota(par.begin() + 1, par.end(), 1);
		siz.assign(n + 1, 1);
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

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto solve = [&]() {
        int n, m1, m2;
        std::cin >> n >> m1 >> m2;

        std::vector<std::pair<int, int>>edgesF;
        for (int i = 1; i <= m1; i += 1) {
            int u, v;
            std::cin >> u >> v;
            edgesF.push_back({u, v});
        }

        DSU dsu(n);
        std::vector<std::pair<int, int>>edgesG;
        for (int i = 1; i <= m2; i += 1) {
            int u, v;
            std::cin >> u >> v;
            edgesG.push_back({u, v});
            dsu.merge(u, v);
        }

        int cnt = 0;
        DSU cof(n);
        std::shuffle(edgesF.begin(), edgesF.end(), rng);
        std::shuffle(edgesF.begin(), edgesF.end(), rng);
        std::shuffle(edgesF.begin(), edgesF.end(), rng);
        std::shuffle(edgesF.begin(), edgesF.end(), rng);
        std::shuffle(edgesF.begin(), edgesF.end(), rng);
        std::shuffle(edgesF.begin(), edgesF.end(), rng);
        std::shuffle(edgesF.begin(), edgesF.end(), rng);
        std::shuffle(edgesF.begin(), edgesF.end(), rng);
        std::shuffle(edgesF.begin(), edgesF.end(), rng);
        std::shuffle(edgesF.begin(), edgesF.end(), rng);
        std::shuffle(edgesF.begin(), edgesF.end(), rng);

        std::shuffle(edgesG.begin(), edgesG.end(), rng);
        std::shuffle(edgesG.begin(), edgesG.end(), rng);
        std::shuffle(edgesG.begin(), edgesG.end(), rng);
        std::shuffle(edgesG.begin(), edgesG.end(), rng);
        std::shuffle(edgesG.begin(), edgesG.end(), rng);
        std::shuffle(edgesG.begin(), edgesG.end(), rng);
        std::shuffle(edgesG.begin(), edgesG.end(), rng);
        std::shuffle(edgesG.begin(), edgesG.end(), rng);
        std::shuffle(edgesG.begin(), edgesG.end(), rng);
        std::shuffle(edgesG.begin(), edgesG.end(), rng);
        std::shuffle(edgesG.begin(), edgesG.end(), rng);

        for (const auto & [u, v] : edgesF) {
            if (!dsu.same(u, v)) {
                cnt += 1;
            } else {
                cof.merge(u, v);
            }
        }

        for (const auto & [u, v] : edgesG) {
            if (!cof.same(u, v)) {
                cnt += 1;
                cof.merge(u, v);
            }
        }
        std::cout << cnt << '\n';
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
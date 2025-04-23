#include<bits/stdc++.h>

using i64 = int64_t;

#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) (void)42
#endif

constexpr int N = 1E3;
int vis[N + 1][N + 1][4];
int dis[N + 1][N + 1][4];

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, m;
	std::cin >> n >> m;

	std::map<std::string, int>Dir;
	Dir["above"] = 0;//up
	Dir["left"] = 1;//le
	Dir["right"] = 2;//ri
	Dir["below"] = 3;//do

	std::vector<std::string>g(n + 1);
	for (int i = 1; i <= n; i += 1) {
		std::cin >> g[i];
		g[i] = " " + g[i];
	}

	auto conver = [&](int x, int y, int dir) {
		std::array<int, 3>res;
		if (g[x][y] == '|') {
			if (dir == 0) {
				res = {x + 1, y, dir};
			} else if (dir == 1) {
				res = {x, y - 1, 3 - dir};
			} else if (dir == 2) {
				res = {x, y + 1, 3 - dir};
			} else {
				res = {x - 1, y, dir};
			}
		} else if (g[x][y] == '-') {
			if (dir == 0) {
				res = {x - 1, y, 3 - dir};
			} else if (dir == 1) {
				res = {x, y + 1, dir};
			} else if (dir == 2) {
				res = {x, y - 1, dir};
			} else {
				res = {x + 1, y, 3 - dir};
			}
		} else if (g[x][y] == '/') {
			if (dir == 0) {
				res = {x, y - 1, 2};
			} else if (dir == 1) {
				res = {x - 1, y, 3};
			} else if (dir == 2) {
				res = {x + 1, y, 0};
			} else {
				res = {x, y + 1, 1};
			}
		} else {
			if (dir == 0) {
				res = {x, y + 1, 1};
			} else if (dir == 1) {
				res = {x + 1, y, 0};
			} else if (dir == 2) {
				res = {x - 1, y, 3};
			} else {
				res = {x, y - 1, 2};
			}
		}
		return res;
	};

	std::set<std::pair<int, int>>S;

	auto work = [&](auto && self, int x, int y, int dir) {
		if (x < 1 or x > n or y < 1 or y > m) {
			return;
		}
		vis[x][y][dir] = 1;
		dis[x][y][dir] = (int)S.size();
		auto [nx, ny, ndir] = conver(x, y, dir);
		if (ndir != dir) {
			S.insert({x, y});
		}
		self(self, nx, ny, ndir);
	};

	for (int i = 1; i <= n; i += 1) {
		S.clear();
		work(work, i, 1, 1);
		S.clear();
		work(work, i, m, 2);
	}
	for (int i = 1; i <= m; i += 1) {
		S.clear();
		work(work, 1, i, 0);
		S.clear();
		work(work, n, i, 3);
	}

	auto dfs = [&](auto && self, int x, int y, int dir) {
		if (vis[x][y][dir]) {
			return (int)S.size();
		}
		vis[x][y][dir] = 1;
		auto [nx, ny, ndir] = conver(x, y, dir);
		if (dir != ndir) {
			S.insert({x, y});
		}
		int &res = dis[x][y][dir] = self(self, nx, ny, ndir);
		return res;
	};

	for (int i = 1; i <= n; i += 1) {
		for (int j = 1; j <= m; j += 1) {
			for (int t = 0; t < 4; t += 1) {
				S.clear();
				dfs(dfs, i, j, t);
			}
		}
	}

	int q;
	std::cin >> q;
	while (q--) {
		std::string s;
		int x, y;
		std::cin >> x >> y >> s;
		std::cout << dis[x][y][Dir[s]] << "\n";
	}

	return 0;
}
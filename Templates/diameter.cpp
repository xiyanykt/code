//1805D
#include<bits/stdc++.h>

using i64 = int64_t;

#include<bits/stdc++.h>

using i64 = int64_t;

struct Diameter {
	int n;
	std::vector<std::vector<int>>adj;
	int x, y;
	std::vector<int>dep, dx, dy;

	Diameter() {}
	Diameter(int n) {
		this->n = n;
		adj.assign(n + 1, std::vector<int>());
	}

	void addEdge(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	void work() {
		auto bfs = [&](int s) {
			std::queue<int>Q;
			dep.assign(n + 1, -1);
			dep[s] = 0;
			Q.push(s);
			while (not Q.empty()) {
				auto u = Q.front();
				Q.pop();
				for (const auto & v : adj[u]) {
					if (dep[v] == -1) {
						dep[v] = dep[u] + 1;
						Q.push(v);
					}
				}
			}
			return std::max_element(dep.begin(), dep.end()) - dep.begin();
		};

		int t = bfs(1);
		x = bfs(t);
		dx = dep;
		y = bfs(x);
		dy = dep;
	}
};

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n; std::cin >> n;
	std::vector adj(n + 1, std::vector<int>());

	for (int i = 1; i <= n - 1; i += 1) {
		int u, v; std::cin >> u >> v;
		adj[u].emplace_back(v), adj[v].emplace_back(u);
	}

	std::vector<int>dep(n + 1, -1);

	auto bfs = [&](int x) {
		std::queue<int>Q;
		dep.assign(n + 1, -1);
		Q.emplace(x), dep[x] = 0;
		while (!Q.empty()) {
			auto u = Q.front(); Q.pop();
			for (const auto & v : adj[u]) {
				if (dep[v] == -1) {
					dep[v] = dep[u] + 1;
					Q.emplace(v);
				}
			}
		}
		return std::max_element(dep.begin() + 1, dep.end()) - dep.begin();
	};

	int x = bfs(1);
	int y = bfs(x);
	auto dx = dep;
	bfs(y);
	auto dy = dep;

	std::vector<int>ans(n + 1);
	for (int i = 1; i <= n; i += 1) {
		ans[std::max(dx[i], dy[i]) + 1] += 1;
	}
	ans[1] += 1, ans[dx[y] + 1] -= 1;
	for (int i = 1; i <= n; i += 1) {
		ans[i] += ans[i - 1];
	}
	for (int i = 1; i <= n; i += 1) {
		std::cout << ans[i] << " \n"[i == n];
	}
	return 0;
}
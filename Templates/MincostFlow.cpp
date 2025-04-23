template <class T>
struct MincostFlow {
	struct edge {
		int to;
		T cap;
		T cost;
		edge(const int& to, const T& cap, const T& cost): to(to), cap(cap), cost(cost) {}
	};
	int n;
	std::vector<edge>e;
	std::vector<std::vector<int>>adj;
	std::vector<T>h, dis;
	std::vector<int>pre;

	bool dijkstra(int s, int t) {
		dis.assign(n, -1);
		pre.assign(n, -1);
		std::priority_queue<std::pair<T,int>, std::vector<std::pair<T,int>>, std::greater<>>Q;
		Q.push({dis[s] = 0, s});
		while (not Q.empty()) {
			auto [d, u] = Q.top();
			Q.pop();
			if (dis[u] != d) {
				continue;
			}
			for (const auto & j : adj[u]) {
				const auto & [v, cap, cost] = e[j];
				if (cap > 0 and (dis[v] == -1 or dis[v] > d + h[u] - h[v] + cost)) {
					pre[v] = j;
					Q.push({dis[v] = d + h[u] - h[v] + cost, v});
				}
			}
		}
		return dis[t] != -1;
	}

	MincostFlow() {

	}
	
	MincostFlow(int n) {
		this->n = n;
		e.clear();
		adj.assign(n, {});
	}

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
		std::vector<Edge>rec;
		for (int i = 0; i < e.size(); i += 2) {
			rec.push_back({.from = e[i + 1].to, .to = e[i].to, .cap = e[i].cap + e[i + 1].cap, .cost = e[i].cost, .flow = e[i + 1].cap});
		}
		return rec;
	}
};
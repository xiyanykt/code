#include<bits/stdc++.h>

using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;

#ifndef ONLINE_JUDGE
#include "algo\debug.hpp"
#else
#define debug(...) (void)42
#endif

int main(void) {
	std::ios::sync_with_stdio(false); std::cin.tie(nullptr); std::cout << std::fixed << std::setprecision(13); auto solve = [&]() {int n; std::cin >> n; std::vector adj(n + 1, std::vector<int>()); std::vector<int>ind(n + 1); for (int i = 1; i <= n; i += 1) {int k; std::cin >> k; for (int j = 1; j <= k; j += 1) {int a; std::cin >> a; adj[a].push_back(i); ind[i] += 1; } } std::vector<int>rec(n + 1); std::queue<int>Q; int cnt = 0; for (int i = 1; i <= n; i += 1) {if (not ind[i]) {Q.push(i); rec[i] = 1; } } while (not Q.empty()) {auto u = Q.front(); Q.pop(); cnt += 1; for (const auto & v : adj[u]) {rec[v] = std::max(rec[v], rec[u] + (u > v)); if (--ind[v] == 0) {Q.push(v); } } } if (cnt != n) {std::cout << "-1\n"; } else {std::cout << std::ranges::max(rec) << "\n"; } }; int t; std::cin >> t; while (t--) {solve(); } return 0;
}
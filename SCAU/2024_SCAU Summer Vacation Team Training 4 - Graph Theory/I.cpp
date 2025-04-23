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
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cout << std::fixed << std::setprecision(13);

	int n, q;
	std::cin >> n >> q;

	std::vector adj(n + 1, std::vector<int>());
	for (int i = 2; i <= n ; i += 1) {
		int x;
		std::cin >> x;
		adj[x].push_back(i);
		adj[i].push_back(x);
	}

	
	return 0;
}
#include<bits/stdc++.h>

using i64 = long long;

auto main()->int32_t{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, k;
	std::cin >> n >> k;

	std::set<int>mask;

	auto dfs = [&](this auto && dfs, int g, int p, int s)->void{
		std::vector<int>factors;
		if (g == 0) {
			for (int j = 1; j <= k; j += 1) {
				factors.push_back(j);
			}
		} else{
			for (int j = 1; j * j <= g; j += 1) {
				if (g % j == 0) {
					factors.push_back(j);
					if (j * j != g) {
						factors.push_back(g / j);
					}
				}
			}
		}
		std::ranges::sort(factors);
		// for (const auto & c : factors) {
		// 	std::cout << c << ' ';
		// }
		// std::cout << '\n';
		for (const auto & v : factors) {
			if (v > k) {
				return;
			}
			if (v >= s) {
				// std::cout << "winer : " << p << '\n';
				mask.insert(p);
				return;
			} else {
				dfs(std::gcd(g, v), p ^ 1, s - v);
			}
		}
	};

	dfs(0, 0, n);

	for (const auto & c : mask) {
		std::cout << c << '\n';
	}

	// std::cout << (dfs(0, 0, n)) << '\n';

	return 0;
}
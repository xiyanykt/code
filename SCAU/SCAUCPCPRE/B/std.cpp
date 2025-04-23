#include<bits/stdc++.h>

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	auto solve = [&]() {
		int n;
		std::cin >> n;
		std::vector<int> a(n + 1);
		for (int i = 1; i <= n; ++i) {
			std::cin >> a[i];
		}
		std::map<int, int> rec;
		for (int i = 1; i <= n; ++i) {
			for (int j = 2; j * j <= a[i]; ++j) {
				while (a[i] % j == 0) {
					a[i] /= j;
					rec[j] += 1;
				}
			}
			if (a[i] != 1)rec[a[i]] += 1;
		}
		
		for (const auto &[x, v] : rec) {
			if (v % n != 0) {
				std::cout << "NO\n";
				return;
			}
		}
		std::cout << "YES\n";
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
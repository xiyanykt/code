#include<bits/stdc++.h>

using i64 = long long;

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout << std::fixed << std::setprecision(13);

	auto solve = [&]() {
		int n;
		std::cin >> n;

		std::vector<int>a(n + 1);
		for (int i = 1; i <= n; i += 1) {
			std::cin >> a[i];
		}

		int x = 0;
		std::vector<int>f(n + 1);
		for (int i = 1; i <= n; i += 1) {
			if (a[i] > x) {
				x += 1;
			} else if (a[i] < x) {
				x -= 1;
			}
			f[i] = std::max(f[i - 1], x);
		}

		std::cout << (*std::ranges::partition_point(std::ranges::iota_view(0, n + 1), [&](int k) {
			for (int i = n; i >= 1; i -= 1) {
				if (f[i - 1] >= k) {
					return true;
				}
				if (k <= a[i]) {
					k -= 1;
				} else {
					k += 1;
				}
			}
			return false;
		}) - 1) << '\n';
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
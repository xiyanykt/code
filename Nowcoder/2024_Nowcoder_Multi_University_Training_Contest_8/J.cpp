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

	constexpr int N = 8;

	auto solve = [&]() {
		int n, m;
		std::cin >> n >> m;
		if (m > n - 3) {
			std::cout << "-1\n";
			return;
		} else if (m == n - 3) {
			for (int i = 1; i <= n; i++) {
				std::cout << i << " ";
			}
			std::cout << "\n";
			return;
		}
		std::vector<int> a(n);
		for (int i = 0; i < n; i++) {
			if (i < n / 2) {
				a[i] = i + 2;
			} else if (i == n / 2) {
				a[i] = 1;
			} else {
				a[i] = i + 1;
			}
		}
		int cnt = n - 4;
		while (cnt > m) {
			for (int i = 3; i < n; i++) {
				int x = a[i - 2], y = a[i - 1], z = a[i];
				int mx = std::max({x, y, z});
				if (mx == x && mx < y + z) {
					for (int j = n - 1; j >= 0; j--) {
						if (a[j] >= y + z) {
							std::swap(a[i - 2], a[j]);
						}
					}
				} else if (mx == y && mx < x + z) {
					for (int j = n - 1; j >= 0; j--) {
						if (a[j] >= x + z) {
							std::swap(a[i - 1], a[j]);
						}
					}
				} else if (mx == z && mx < y + x) {
					for (int j = n - 1; j >= 0; j--) {
						if (a[j] >= y + x) {
							std::swap(a[i], a[j]);
						}
					}
				}
			}
			cnt--;
		}


		for (int i = 0; i < n; i++) {
			std::cout << a[i] << " \n"[i == n - 1];
		}
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}

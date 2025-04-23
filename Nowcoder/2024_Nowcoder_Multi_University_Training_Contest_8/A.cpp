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

	constexpr int N = 1E5;

	auto solve = [&]() {
		int n;
		std::cin >> n;

		std::vector<int>rec(N + 1);
		for (int i = 1; i <= n; i += 1) {
			int x;
			std::cin >> x;
			rec[x] += 1;
		}

		for (int i = N; i >= 1; i -= 1) {
			int g = 0;
			for (int j = 2 * i; j <= N; j += i) {
				if (rec[j]) {
					g = std::gcd(g, j / i);
				}
			}
			if (g == 1) {
				rec[i] += 1;
			}
		}

		int ans = 0;
		for (int i = 1; i <= N; i += 1) {
			ans += !!rec[i];
		}
		ans -= n;
		std::cout << (ans % 2 == 1 ? "dXqwq\n" : "Haitang\n");
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
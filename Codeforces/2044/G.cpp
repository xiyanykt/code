#include<bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f64 = long double;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

template<class T>
constexpr bool chmax(T& x, T y) {
	if (y > x) {
		x = y;
		return true;
	}
	return false;
}

template<class T>
constexpr bool chmin(T& x, T y) {
	if (y < x) {
		x = y;
		return true;
	}
	return false;
}

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	auto solve = [&]() {
		int n;
		std::cin >> n;

		std::vector<int>r(n + 1);
		for (int i = 1; i <= n; i += 1) {
			std::cin >> r[i];
		}

		std::vector<int>d(n + 1, -1);
		for (int i = 1; i <= n; i += 1) {
			if (d[i] != -1) {
				continue;
			}
			std::vector<int>c;
			int j = i;
			while (d[j] == -1) {
				c.push_back(j);
				d[j] = 0;
				j = r[j];
			}
			c.erase(std::ranges::find(c, j), c.end());
			for (int k = 0; k < c.size(); k += 1) {
				d[c[k]] = d[j] + c.size() - k;
			}
		}

		std::cout << std::ranges::max(d) + 2 << '\n';
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
#include<bits/stdc++.h>
using i64 = long long;
constexpr int Mod = 1E9 + 7;

static constexpr int power(int a, int b) {
	int res = 1;
	for (; b != 0; b >>= 1, a = i64(a) * a % Mod) {
		if (b & 1) {
			res = i64(res) * a % Mod;
		}
	}
	return res;
}

static constexpr int add(int a, int b) {
	return (a + b) % Mod;
}

static constexpr int mul(int a, int b) {
	return i64(a) * b % Mod;
}

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n;
	std::cin >> n;

	std::vector<int>a(n + 1);
	for (int i = 1; i <= n; i += 1) {
		std::cin >> a[i];
	}

	int ans = 0;
	for (int s = 0; s < (1 << n); s += 1) {
		std::set<int>t;
		for (int i = 1; i <= n; i += 1) {
			if (s >> (i - 1) & 1) {
				t.insert(a[i]);
			}
		}
		int x = 0;
		while (t.contains(x)) {
			x += 1;
		}
		ans += x;
	}
	std::cout << ans << '\n';
	return 0;
}
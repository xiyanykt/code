#include<bits/stdc++.h>

using i64 = long long;

constexpr int Mod = 998244353;
constexpr int inf = 1E9;

constexpr int add(int a, int b) {
	return (i64(a) + b) % Mod;
}

constexpr int mul(int a, int b) {
	return (i64(a) * b) % Mod;
}

void solve() {
	int n, k;
	std::cin >> n >> k;

	std::cout << ((n & -n) <= k ? "Alice\n" : "Bob\n");
}

auto main()->int32_t{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int t = 1;
	std::cin >> t;

	while (t--) {
		solve();
	}

	return 0;
}
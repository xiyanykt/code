#include<bits/stdc++.h>

using i64 = long long;

#define int long long

constexpr int Mod = 998244353;
constexpr int inf = 1E9;

constexpr int add(int a, int b) {
	return (i64(a) + b) % Mod;
}

constexpr int mul(int a, int b) {
	return (i64(a) * b) % Mod;
}

void solve() {
	int n;
	std::cin >> n;

	std::vector<int>a(n + 1);
	for (int i = 1; i <= n; i += 1) {
		std::cin >> a[i];
	}

	std::sort(a.begin() + 1, a.end());
	// std::sort(a.begin() + 1, a.end(), std::greater());


	if (n == 1) {
		std::cout << 0 << ' ' << 1 << '\n';
		return ;
	}

	i64 ans = 0;
	for (int l = 1; l <= n; l += 1) {
		int min = inf, max = 0;
		for (int  r = l; r <= n; r += 1) {
			max = std::max(max, a[r]);
			min = std::min(min, a[r]);
			ans += max - min;
		}
	}

	std::map<int, int>rec;
	for (int i = 1; i <= n; i += 1) {
		rec[a[i]] += 1;
	}

	int cnt = 2;
	std::vector<int>fac(n + 1);
	fac[1] = 1;
	for (int i = 2; i <= n; i += 1) {
		fac[i] = mul(fac[i - 1], i);
	}

	for (const auto & [x, v] : rec) {
		cnt = mul(cnt, fac[v]);
	}

	std::cout << ans << ' ' << cnt << '\n';
}

auto main()->int32_t{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int t = 1;
	// std::cin >> t;

	while (t--) {
		solve();
	}

	return 0;
}
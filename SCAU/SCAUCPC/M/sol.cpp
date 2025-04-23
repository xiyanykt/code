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

	std::map<int, int>rec;
	for (int i = 1; i <= n; i += 1) {
		rec[a[i]] += 1;
	}

	int ans = 0, cnt = n - rec[0], pre = 1;
	for (int x = 1; x <= n; x += 1) {
		if (!rec.contains(x - 1)) {
			break;
		}
		pre = mul(pre, rec[x - 1]);
		cnt -= rec[x];
		ans = add(ans, mul(x, mul(pre, power(2, cnt))));
	}
	std::cout << ans << '\n';
	return 0;
}
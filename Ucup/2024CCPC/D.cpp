#include<bits/stdc++.h>

using i64 = int64_t;

constexpr int Mod = 998244353;
constexpr int inf = 1E9;

constexpr int add(int a, int b) {
	return (i64(a) + b) % Mod;
}

constexpr int mul(int a, int b) {
	return (i64(a) * b) % Mod;
}

constexpr int power(int a, int b) {
	int res = 1;
	for (; b != 0; b >>= 1, a = mul(a, a)) {
		if (b % 2 == 1) {
			res = mul(res, a);
		}
	}
	return res;
}

constexpr int inv(int x) {
	return power(x, Mod - 2);
}

auto main()->int32_t{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);



	return 0;
}
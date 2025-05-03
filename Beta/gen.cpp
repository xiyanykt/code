#include<bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f64 = long double;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

i64 rand(i64 l, i64 r) {
	return std::uniform_int_distribution<i64>(l, r)(rng);
}

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cout << 10 << '\n';
	for (int i = 1; i <= 10; i += 1) {
		std::cout << "0123456789"[rand(0, 9)];
	}
	return 0;
}
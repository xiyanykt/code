#include<bits/stdc++.h>
using i64 = long long;

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

template <typename T>
T rand(T l, T r) {
	return std::uniform_int_distribution<T>(l, r)(rng);
}

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	constexpr int Kn = 17;
	constexpr int lo = 1;
	constexpr int hi = 1E9;

	std::cout << Kn << '\n';

	int w = rand(1, int(1E6));
	std::vector<i64>pool;
	for (int k = 1; i64(k) * w <= hi; k += 1) {
		pool.push_back(i64(k) * w);
	}

	int m = pool.size();
	// std::cerr << w << '\n';

	for (int i = 1; i <= Kn; i += 1) {
		std::cout << pool[rand(0, m - 1)] << ' ' << pool[rand(0, m - 1)] << '\n';
	}
	return 0;
}
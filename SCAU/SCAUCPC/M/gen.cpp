#include<bits/stdc++.h>
using i64 = long long;

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

template <class T>
T rand(T l, T r) {
	return std::uniform_int_distribution<T>(l, r)(rng);
}

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	constexpr int N = 19;
	constexpr int W = 19;

	std::cout << N << '\n';
	for (int i = 1; i <= N; i += 1) {
		std::cout << rand(1, W) << " \n"[i == N];
	}

	return 0;
}
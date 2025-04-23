#include<bits/stdc++.h>

using i64 = long long;

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int rand(int l, int r) {
	return std::uniform_int_distribution<int>(l, r)(rng);
}

auto main()->int32_t{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	constexpr int N = 1;
	std::cout << N << '\n';

	constexpr int X = 1E6;
	for (int i = 1; i <= N; i += 1) {
		int x = rand(1, X);
		std::cout << x << " \n"[i == N];
	}

	return 0;
}
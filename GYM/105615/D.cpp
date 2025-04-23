#include<bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f64 = long double;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

#include"W:\v\algo\debug.hpp"

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

	// int n;
	// std::cin >> n;

	// std::vector<int>p(n);
	// std::ranges::iota(p, 1);

	// int x = 1E9;
	// do {
	// 	int y = 0;
	// 	for (int i = 0; i < n - 1; i += 1) {
	// 		y += std::gcd(p[i] + 1, p[i + 1]);
	// 	}
	// 	chmin(x, y);
	// } while (std::ranges::next_permutation(p).found);


	// do {
	// 	int y = 0;
	// 	for (int i = 0; i < n - 1; i += 1) {
	// 		y += std::gcd(p[i] + 1, p[i + 1]);
	// 	}
	// 	if (y == x) {
	// 		debug(p);
	// 	}
	// } while (std::ranges::next_permutation(p).found);


	auto solve = [&]() {
		int n;
		std::cin >> n;

		for (const int & x : std::views::iota(1, n + 1)) {
			if (x % 2 == 0) {
				std::cout << x << ' ';
			}
		}

		for (const int & x : std::views::iota(1, n + 1)) {
			if (x % 2 == 1) {
				std::cout << x << ' ';
			}
		}

		std::cout << '\n';
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
#include<bits/stdc++.h>

using i64 = long long;

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int rand(int l, int r) {
	return std::uniform_int_distribution<int>(l, r)(rng);
}

auto main()->int32_t{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int t = 0;
	while (true) {
		std::cout << "test : " << ++t << std::endl;
		system("data.exe > data.in");
		system("std.exe < data.in > std.out");
		system("sol.exe < data.in > sol.out");
		if (system("fc std.out sol.out > diff.log")) {
			std::cout << "WA" << std::endl;
			break;
		}
		std::cout << "AC" << std::endl;
	}

	return 0;
}
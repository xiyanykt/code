#include<bits/stdc++.h>

using i64 = long long;

auto main() -> int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	system("compileGen.bat");
	system("compileStd.bat");
	system("compileSol.bat");

	int c = 1;
	while (true) {
		system("gen.exe > f.in");
		system("std.exe < f.in > std.out");
		system("sol.exe < f.in > sol.out");
		if (system("fc std.out sol.out > nul") != 0) {
			break;
		} else {
			std::cout << std::format("test : {} \nAC\n", c++) << std::endl;
		}
	}
	std::cout << std::format("test : {} \nWA\n", c) << std::endl;
	return 0;
}

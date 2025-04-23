#include<bits/stdc++.h>

using i64 = int64_t;

#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) (void)42
#endif

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

#define int i64

	i64 n, u, v;
	std::cin >> n >> u >> v;

	std::string s;
	std::cin >> s;
	s = " " + s;

	if (u == 0 and v == 0) {
		std::cout << (1LL * n * (n + 1) / 2) << "\n";
		return 0;
	}

	constexpr i64 Dx = 1E8;

	std::map<i64, int>rec;
	rec[0] = n + 1;
	i64 ans = 0;
	i64 sum = 0;
	for (int i = n; i >= 1; i -= 1) {
		if (s[i] == 'W') {
			sum += Dx;
		} else if (s[i] == 'S') {
			sum -= Dx;
		} else if (s[i] == 'A') {
			sum -= 1;
		} else {
			sum += 1;
		}
		rec[sum] = i;
		if (rec.contains(sum - u - v * Dx)) {
			ans += n - rec[sum - u - v * Dx] + 2;
		}
	}

	std::cout << ans << "\n";
	return 0;
}
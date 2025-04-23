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

	int n, k;
	std::cin >> n >> k;

	std::vector<i64>a(n + 1);
	for (int i = 1; i <= n; i += 1) {
		std::cin >> a[i];
		a[i] += 1;
	}
	std::vector<i64>c(n + 2), f(n + 2), g(n + 2);

	auto work = [&](i64 d) {
		i64 res = 0;
		c.assign(n + 2, 0);
		f.assign(n + 2, 0);
		g.assign(n + 2, 0);
		for (int i = n; i >= 1; i -= 1) {
			c[i] += c[i + 1], f[i] += f[i + 1], g[i] += g[i + 1];
			i64 x = a[i] - (1LL * c[i] * d - f[i] + 1LL * g[i] * i - 1LL * c[i] * i * i);
			if (x <= 0) {
				continue;
			}
			int clz = std::sqrt(d);
			int cnt = 1LL * (x + d - 1) / d;
			res += cnt;
			c[i - 1] += cnt;
			f[i - 1] += 1LL * cnt * i * i;
			g[i - 1] += 2LL * cnt * i;
			if (i - clz - 1 >= 1) {
				c[i - clz - 1] -= cnt;
				f[i - clz - 1] -= 1LL * cnt * i * i;
				g[i - clz - 1] -= 2LL * cnt * i;
			}
		}
		return res <= k;
	};

	i64 lo = 1, hi = 1E14;
	while (lo <= hi) {
		auto mid = std::midpoint(lo, hi);
		if (work(mid)) {
			hi = mid - 1;
		} else {
			lo = mid + 1;
		}
	}

	std::cout << hi + 1 << "\n";

	return 0;
}
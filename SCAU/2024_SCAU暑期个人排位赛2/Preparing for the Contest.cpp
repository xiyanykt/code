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

	int n, m, s;
	std::cin >> n >> m >> s;

	std::vector<int>a(m + 1), b(n + 1), c(n + 1);
	for (int i = 1; i <= m; i += 1) {
		std::cin >> a[i];
	}
	for (int i = 1; i <= n; i += 1) {
		std::cin >> b[i];
	}
	for (int i = 1; i <= n; i += 1) {
		std::cin >> c[i];
	}

	std::vector<int>p(m + 1);
	std::iota(p.begin(), p.end(), 0);
	std::sort(p.begin() + 1, p.end(), [&](const auto & i, const auto & j) {
		return a[i] < a[j];
	});

	std::vector<int>e(n + 1);
	std::iota(e.begin(), e.end(), 0);
	std::sort(e.begin() + 1, e.end(), [&](const auto & i, const auto & j) {
		return b[i] == b[j] ? c[i] > c[j] : b[i] < b[j];
	});

	std::vector<int>ans(m + 1);
	auto work = [&](int x) {
		i64 res = 0;
		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>>Q;
		for (int i = m, j = n; i >= 1; i -= 1) {
			while (j >= 1 and b[e[j]] >= a[p[i]]) {
				Q.emplace(c[e[j]], e[j]);
				j -= 1;
			}
			if (Q.empty()) {
				return true;
			}
			auto u = Q.top();
			res += u.first;
			for (int l = i; l >= std::max(1, i - x + 1); l -= 1) {
				ans[p[l]] = u.second;
			}
			Q.pop();
			i -= x - 1;
		}
		if (res <= s) {
			return false;
		}
		return true;
	};

	int o = *std::ranges::partition_point(std::ranges::iota_view(1, m + 1), work);

	if (o == m + 1) {
		std::cout << "NO\n";
	} else {
		std::cout << "YES\n";
		work(o);
		for (int i = 1; i <= m; i += 1) {
			std::cout << ans[i] << " \n"[i == m];
		}
	}

	return 0;
}
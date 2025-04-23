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

	int n, q;
	std::cin >> n >> q;

	std::vector<i64>a(n + 1), e(n + 1);
	for (int i = 1; i <= n; i += 1) {
		std::cin >> a[i];
	}

	const int B = sqrt(n);
	const int T = (n + B - 1) / B;
	std::vector<int>bel(n + 1), L(T + 1), R(T + 1);
	std::vector<i64>add(T + 1);

	auto cg = [&](int p) {
		for (int j = L[p]; j <= R[p]; j += 1) {
			e[j] = a[j];
		}
		std::sort(e.begin() + L[p], e.begin() + R[p] + 1);
	};

	for (int i = 1; i <= T; i += 1) {
		L[i] = (i - 1) * B + 1;
		R[i] = std::min(n, i * B);
		for (int j = L[i]; j <= R[i]; j += 1) {
			bel[j] = i;
		}
		cg(i);
	}

	while (q--) {
		std::string op;
		int l, r, c;
		std::cin >> op >> l >> r >> c;
		if (op == "A") {
			int ans = 0;
			if (bel[l] == bel[r]) {
				for (int j = l; j <= r; j += 1) {
					ans += (a[j] >= c - add[bel[j]]);
				}
			} else {
				for (int j = l; j <= R[bel[l]]; j += 1) {
					ans += (a[j] >= c - add[bel[j]]);
				}
				for (int j = L[bel[r]]; j <= r; j += 1) {
					ans += (a[j] >= c - add[bel[j]]);
				}
				for (int j = bel[l] + 1; j <= bel[r] - 1; j += 1) {
					ans += R[j] - (std::lower_bound(e.begin() + L[j], e.begin() + R[j] + 1, c - add[j]) - e.begin()) + 1;
				}
			}
			std::cout << ans << "\n";
		} else {
			if (bel[l] == bel[r]) {
				for (int j = l; j <= r; j += 1) {
					a[j] += c;
				}
				cg(bel[l]);
			} else {
				for (int j = l; j <= R[bel[l]]; j += 1) {
					a[j] += c;
				}
				for (int j = L[bel[r]]; j <= r; j += 1) {
					a[j] += c;
				}
				cg(bel[l]);
				cg(bel[r]);
				for (int j = bel[l] + 1; j <= bel[r] - 1; j += 1) {
					add[j] += c;
				}
			}
		}
	}
	return 0;
}
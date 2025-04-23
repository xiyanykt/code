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

	int n, k, l, r, sa, sk;
	std::cin >> n >> k >> l >> r >> sa >> sk;

	if (n == k) {
		int ave = sa / n;
		int lef = sa % n;
		for (int i = 1; i <= n; i += 1) {
			if (lef > 0) {
				lef -= 1;
				std::cout << ave + 1 << " ";
			} else {
				std::cout << ave << " ";
			}
		}
	} else {
		int sma = n - k;
		int sm = sa - sk;

		int ave = sm / sma;
		int lef = sm % sma;
		for (int i = 1; i <= sma; i += 1) {
			if (lef > 0) {
				lef -= 1;
				std::cout << ave + 1 << " ";
			} else {
				std::cout << ave << " ";
			}
		}

		int v = ave;

		if (sm % sma) {
			v += 1;
		}

		int sti = v * k;
		sti = sk - sti;
		v += sti / k;
		lef = sti % k;
		for (int i = 1; i <= k; i += 1) {
			if (lef > 0) {
				lef -= 1;
				std::cout << v + 1 << " ";
			} else {
				std::cout << v << " ";
			}
		}
	}

	return 0;
}
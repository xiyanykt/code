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

	int n;
	std::cin >> n;

	std::string s;
	std::cin >> s;
	s = " " + s;

	int pre = 0, suf = 0, cntP = 0, cntS = 0;
	for (int i = 1; i <= n; i += 1) {
		if (i <= n / 2) {
			if (s[i] == '?') {
				cntP += 1;
			} else {
				pre += s[i] - '0';
			}
		} else {
			if (s[i] == '?') {
				cntS += 1;
			} else {
				suf += s[i] - '0';
			}
		}
	}

	if (cntS == cntP) {
		std::cout << (pre == suf ? "Bicarp\n" : "Monocarp\n");
	} else if (cntS > cntP) {
		int op = (cntS - cntP) / 2;
		if (suf >= pre) {
			std::cout << "Monocarp\n";
		} else {
			std::cout << (suf + op * 9 == pre ? "Bicarp\n" : "Monocarp\n");
		}
	} else {
		int op = (cntP - cntS) / 2;
		if (pre >= suf) {
			std::cout << "Monocarp\n";
		} else {
			std::cout << (pre + op * 9 == suf ? "Bicarp\n" : "Monocarp\n");
		}
	}

	return 0;
}
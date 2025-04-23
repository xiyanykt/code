#include<bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f64 = long double;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

#ifndef ONLINE_JUDGE
#include "algo/debug.hpp"
#else
#define debug(...) (void)42
#endif

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

constexpr int Kt = 6;

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	auto solve = [&]() {
		int n;
		std::cin >> n;

		std::map<char, int>rec;
		for (int i = 0; i < n; i += 1) {
			std::string s;
			std::cin >> s;
			rec[s.back()] += 1;
		}

		std::array<int, Kt> t {};
		for (int i = 0; i < Kt; i += 1) {
			std::cin >>  t[i];
		}

		int cnt = 0;
		int mod = 0;
		for (const auto & c : "DCHS") {
			cnt += rec[c] / 5;
			mod += (rec[c] %= 5);
		}

		std::string ord = "DCHS";
		for (int j = 0; j < 4; j += 1) {
			if (mod >= 5 && rec[ord[j]] + t[Kt - 1] + t[Kt - 2] >= 5) {
				cnt += 1;
				if (rec[ord[j]] == 3) {
					t[Kt - 1] = 0;
					t[Kt - 2] = 0;
				}
				if (rec[ord[j]] == 4) {
					if (t[Kt - 1]) {
						t[Kt - 1] = 0;
					} else if (t[Kt - 2]) {
						t[Kt - 2] = 0;
					}
				}
				rec[ord[j]] = 0;
				mod -= 5;
			}
		}
		
		for (int j = 0; j < 4; j += 1) {
			if (t[j] > 0 && rec[ord[j]] >= 2 - t[Kt - 2] - t[Kt - 1] && mod >= 5) {
				cnt += 1;
				t[j] = 0;
				if (rec[ord[j]] == 0) {
					t[Kt - 1] = 0;
					t[Kt - 2] = 0;
				}
				if (rec[ord[j]] == 1) {
					if (t[Kt - 1]) {
						t[Kt - 1] = 0;
					} else if (t[Kt - 2]) {
						t[Kt - 2] = 0;
					}
				}
				rec[ord[j]] = 0;
				mod -= 5;
			}
		}

		std::cout << cnt << '\n';
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
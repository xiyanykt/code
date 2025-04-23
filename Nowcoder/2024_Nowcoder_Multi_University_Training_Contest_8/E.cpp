#include<bits/stdc++.h>

#pragma GCC optimize("O2")
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
#pragma GCC target("sse4,popcnt,abm,mmx")

using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;

#ifndef ONLINE_JUDGE
#include "algo\debug.hpp"
#else
#define debug(...) (void)42
#endif

i64 mul(i64 a, i64 b, i64 m) {
	return static_cast<__int128>(a) * b % m;
}

i64 power(i64 a, i64 b, i64 m) {
	i64 res = 1 % m;
	for (; b; b >>= 1, a = mul(a, a, m)) {
		if (b & 1) {
			res = mul(res, a, m);
		}
	}
	return res;
}

bool isPrime(i64 n) {
	if (n < 2) {
		return false;
	}
	static constexpr int A[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
	int s = __builtin_ctzll(n - 1);
	i64 d = (n - 1) >> s;
	for (const auto & a : A) {
		if (a == n) {
			return true;
		}
		i64 x = power(a, d, n);
		if (x == 1 or x == n - 1) {
			continue;
		}
		bool ok = false;
		for (int i = 0; i < s - 1; i += 1) {
			x = mul(x, x, n);
			if (x == n - 1) {
				ok = true;
				break;
			}
		}
		if (not ok) {
			return false;
		}
	}
	return true;
}

constexpr int M = 1E4;

std::vector<i64> factorize_Prime(i64 n) {
	std::vector<i64>p;
	auto func = [&](auto && self, i64 n)->void{
		if (n <= M) {
			for (int i = 2; i * i <= n; ++i)
				for (; n % i == 0; n /= i)
					p.push_back(i);
			if (n > 1)
				p.push_back(n);
			return;
		}
		if (isPrime(n)) {
			p.push_back(n);
			return;
		}
		auto g = [&](i64 x) {
			return (mul(x, x, n) + 1) % n;
		};
		i64 x0 = 2;
		while (true) {
			i64 x = x0, y = x0, d = 1;
			i64 power = 1, lam = 0, v = 1;
			while (d == 1) {
				y = g(y);
				lam += 1;
				v = mul(v, std::abs(x - y), n);
				if (lam % 127 == 0) {
					d = std::gcd(v, n);
					v = 1;
				}
				if (power == lam) {
					x = y;
					power <<= 1;
					lam = 0;
					d = std::gcd(v, n);
					v = 1;
				}
			}
			if (d != n) {
				self(self, d);
				self(self, n / d);
				return;
			}
			x0 += 1;
		}
	};
	func(func, n);
	std::sort(p.begin(), p.end());
	return p;
}

std::vector<i64> factorize(const auto & facp, i64 n) {
	std::vector<i64>div;
	std::vector<std::pair<i64, int>>divp;
	for (const auto & c : facp) {
		if (divp.empty() or c != divp.back().first) {
			divp.push_back({c, 1});
		} else {
			divp.back().second += 1;
		}
	}
	auto dfs = [&](auto && self, int u, i64 p) {
		if (u >= divp.size()) {
			div.push_back(p);
			return;
		}
		for (int f = 0; f <= divp[u].second; f += 1) {
			self(self, u + 1, p);
			p *= divp[u].first;
		}
	};
	dfs(dfs, 0, (i64)1);
	return div;
}

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	auto solve = [&]() {
		i64 n;
		std::cin >> n;

		auto cal = [&](i64 x) {
			int res = 0;
			for (; x > 0; x /= 10) {
				res += x % 10;
			}
			return res;
		};

		int ans = 0;
		for (int j = 1; j <= 126 and n >= j; j += 1) {
			i64 f = n - j;
			auto res = factorize(factorize_Prime(f), f);
			for (const auto & c : res) {
				if (n % c == j and cal(c) == j and c <= n) {
					ans += 1;
				}
			}
		}
		std::cout << ans << "\n";
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
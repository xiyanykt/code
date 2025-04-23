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
using i128 = __int128;

#ifndef ONLINE_JUDGE
#include "algo\debug.hpp"
#else
#define debug(...) (void)42
#endif

std::istream &operator>>(std::istream &is, i128 &n) {
	std::string s;
	is >> s;
	n = 0;
	for (int i = (s[0] == '-'); i < s.size(); i += 1) {
		n = n * 10 + s[i] - '0';
	}
	if (s[0] == '-') {
		n *= -1;
	}
	return is;
}

std::ostream &operator<<(std::ostream &os, i128 n) {
	std::string s;
	if (n == 0) {
		return os << 0;
	}
	bool sign = false;
	if (n < 0) {
		sign = true;
		n = -n;
	}
	while (n > 0) {
		s += '0' + n % 10;
		n /= 10;
	}
	if (sign) {
		s += '-';
	}
	std::reverse(s.begin(), s.end());
	return os << s;
}

template<class T>
void chmax(T& x, T y) {
	x = std::max(x, y);
}

template<class T>
void chmin(T& x, T y) {
	x = std::min(x, y);
}

i128 power(i128 a, i128 b) {
	i128 res = 1;
	while (b > 0) {
		if (b % 2 == 1) {
			res *= a;
		}
		a *= a;
		b /= 2;
	}
	return res;
}

i128 lower(i128 x) {
	i128 lo = 0, hi = 1E18;
	while (lo <= hi) {
		i128 mid = (lo + hi) / 2;
		if (mid * mid <= x) {
			lo = mid + 1;
		} else {
			hi = mid - 1;
		}
	}
	return lo - 1;
}

i128 upper(i128 x) {
	i128 lo = 0, hi = 1E18;
	while (lo <= hi) {
		i128 mid = (lo + hi) / 2;
		if (mid * mid >= x) {
			hi = mid - 1;
		} else {
			lo = mid + 1;
		}
	}
	return hi + 1;
}

i128 Strtoi128(const std::string &s) {
	i128 n = 0;
	for (const auto & c : s) {
		n = n * 10 + c - '0';
	}
	return n;
}

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n;
	std::cin >> n;

	std::string l, r;
	std::cin >> l >> r;

	i128 l_left = Strtoi128(l.substr(0, n / 2));
	i128 l_right = Strtoi128(l.substr(n / 2));
	i128 r_left = Strtoi128(r.substr(0, n / 2));
	i128 r_right = Strtoi128(r.substr(n / 2));

	i128 ans = 0;

	i128 x = upper(l_left);
	i128 y = lower(r_left);
	i128 u = lower(power(10, n / 2) - 1);

	ans += (y - x + 1) * (u + 1);

	if (x * x == l_left) {
		ans -= u + 1;
		ans += (u - upper(l_right) + 1);
	}

	if (y * y == r_left) {
		ans -= u + 1;
		ans += lower(r_right) + 1;
	}

	std::cout << ans << "\n";

	return 0;
}

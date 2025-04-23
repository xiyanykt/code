#include<bits/stdc++.h>

using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128_t;
using f128 = __float128;

#ifndef ONLINE_JUDGE
#include "algo/debug.hpp"
#else
#define debug(...) (void)42
#endif

template<class T>
constexpr void chmax(T& x, T y) {
	if (y > x) {
		x = y;
	}
}

template<class T>
constexpr void chmin(T& x, T y) {
	if (y < x) {
		x = y;
	}
}

template<class T>
struct Frac {
	T num;
	T den;
	Frac(T num_, T den_) : num(num_), den(den_) {
		if (den < 0) {
			den = -den;
			num = -num;
		}
	}
	Frac() : Frac(0, 1) {}
	Frac(T num_) : Frac(num_, 1) {}
	explicit operator double() const {
		return 1. * num / den;
	}
	Frac &operator+=(const Frac &rhs) {
		num = num * rhs.den + rhs.num * den;
		den *= rhs.den;
		return *this;
	}
	Frac &operator-=(const Frac &rhs) {
		num = num * rhs.den - rhs.num * den;
		den *= rhs.den;
		return *this;
	}
	Frac &operator*=(const Frac &rhs) {
		num *= rhs.num;
		den *= rhs.den;
		return *this;
	}
	Frac &operator/=(const Frac &rhs) {
		num *= rhs.den;
		den *= rhs.num;
		if (den < 0) {
			num = -num;
			den = -den;
		}
		return *this;
	}
	friend Frac operator+(Frac lhs, const Frac &rhs) {
		return lhs += rhs;
	}
	friend Frac operator-(Frac lhs, const Frac &rhs) {
		return lhs -= rhs;
	}
	friend Frac operator*(Frac lhs, const Frac &rhs) {
		return lhs *= rhs;
	}
	friend Frac operator/(Frac lhs, const Frac &rhs) {
		return lhs /= rhs;
	}
	friend Frac operator-(const Frac &a) {
		return Frac(-a.num, a.den);
	}
	friend bool operator==(const Frac &lhs, const Frac &rhs) {
		return lhs.num * rhs.den == rhs.num * lhs.den;
	}
	friend bool operator!=(const Frac &lhs, const Frac &rhs) {
		return lhs.num * rhs.den != rhs.num * lhs.den;
	}
	friend bool operator<(const Frac &lhs, const Frac &rhs) {
		return lhs.num * rhs.den < rhs.num * lhs.den;
	}
	friend bool operator>(const Frac &lhs, const Frac &rhs) {
		return lhs.num * rhs.den > rhs.num * lhs.den;
	}
	friend bool operator<=(const Frac &lhs, const Frac &rhs) {
		return lhs.num * rhs.den <= rhs.num * lhs.den;
	}
	friend bool operator>=(const Frac &lhs, const Frac &rhs) {
		return lhs.num * rhs.den >= rhs.num * lhs.den;
	}
	friend std::ostream &operator<<(std::ostream &os, Frac x) {
		T g = std::gcd(x.num, x.den);
		if (false) {
			return os << x.num / g;
		} else {
			return os << x.num / g << " " << x.den / g;
		}
	}
};

using F = Frac<i64>;

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout << std::fixed << std::setprecision(13);

	auto solve = [&]() {
		int n;
		std::cin >> n;

		int x = std::sqrt(2 * n);
		constexpr int inf = 1E9;
		F ans = {inf, 1};
		for (int y = std::max(1, x - 3); y <= x + 3; y += 1) {
			F a = {y - 1, 2};
			F b = {n, y};
			ans = std::min(ans, a + b);
		}
		std::cout << ans << '\n';
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
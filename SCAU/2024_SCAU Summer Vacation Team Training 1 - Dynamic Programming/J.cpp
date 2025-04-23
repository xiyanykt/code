#include <bits/stdc++.h>

using i64 = int64_t;
template<class T>
constexpr T power(T a, i64 b) {
	T res = 1;
	for (; b; b /= 2, a *= a) {
		if (b % 2) {
			res *= a;
		}
	}
	return res;
}

constexpr i64 mul(i64 a, i64 b, i64 p) {
	i64 res = a * b - i64(1.L * a * b / p) * p;
	res %= p;
	if (res < 0) {
		res += p;
	}
	return res;
}
template<i64 P>
struct MLong {
	i64 x;
	constexpr MLong() : x{} {}
	constexpr MLong(i64 x) : x{norm(x % getMod())} {}

	static i64 Mod;
	constexpr static i64 getMod() {
		if (P > 0) {
			return P;
		} else {
			return Mod;
		}
	}
	constexpr static void setMod(i64 Mod_) {
		Mod = Mod_;
	}
	constexpr i64 norm(i64 x) const {
		if (x < 0) {
			x += getMod();
		}
		if (x >= getMod()) {
			x -= getMod();
		}
		return x;
	}
	constexpr i64 val() const {
		return x;
	}
	explicit constexpr operator i64() const {
		return x;
	}
	constexpr MLong operator-() const {
		MLong res;
		res.x = norm(getMod() - x);
		return res;
	}
	constexpr MLong inv() const {
		assert(x != 0);
		return power(*this, getMod() - 2);
	}
	constexpr MLong &operator*=(MLong rhs) & {
		x = mul(x, rhs.x, getMod());
		return *this;
	}
	constexpr MLong &operator+=(MLong rhs) & {
		x = norm(x + rhs.x);
		return *this;
	}
	constexpr MLong &operator-=(MLong rhs) & {
		x = norm(x - rhs.x);
		return *this;
	}
	constexpr MLong &operator/=(MLong rhs) & {
		return *this *= rhs.inv();
	}
	friend constexpr MLong operator*(MLong lhs, MLong rhs) {
		MLong res = lhs;
		res *= rhs;
		return res;
	}
	friend constexpr MLong operator+(MLong lhs, MLong rhs) {
		MLong res = lhs;
		res += rhs;
		return res;
	}
	friend constexpr MLong operator-(MLong lhs, MLong rhs) {
		MLong res = lhs;
		res -= rhs;
		return res;
	}
	friend constexpr MLong operator/(MLong lhs, MLong rhs) {
		MLong res = lhs;
		res /= rhs;
		return res;
	}
	friend constexpr std::istream &operator>>(std::istream &is, MLong &a) {
		i64 v;
		is >> v;
		a = MLong(v);
		return is;
	}
	friend constexpr std::ostream &operator<<(std::ostream &os, const MLong &a) {
		return os << a.val();
	}
	friend constexpr bool operator==(MLong lhs, MLong rhs) {
		return lhs.val() == rhs.val();
	}
	friend constexpr bool operator!=(MLong lhs, MLong rhs) {
		return lhs.val() != rhs.val();
	}
};

template<>
i64 MLong<0LL>::Mod = 1;

template<int P>
struct MInt {
	int x;
	constexpr MInt() : x{} {}
	constexpr MInt(i64 x) : x{norm(x % getMod())} {}

	static int Mod;
	constexpr static int getMod() {
		if (P > 0) {
			return P;
		} else {
			return Mod;
		}
	}
	constexpr static void setMod(int Mod_) {
		Mod = Mod_;
	}
	constexpr int norm(int x) const {
		if (x < 0) {
			x += getMod();
		}
		if (x >= getMod()) {
			x -= getMod();
		}
		return x;
	}
	constexpr int val() const {
		return x;
	}
	explicit constexpr operator int() const {
		return x;
	}
	constexpr MInt operator-() const {
		MInt res;
		res.x = norm(getMod() - x);
		return res;
	}
	constexpr MInt inv() const {
		assert(x != 0);
		return power(*this, getMod() - 2);
	}
	constexpr MInt &operator*=(MInt rhs) & {
		x = 1LL * x * rhs.x % getMod();
		return *this;
	}
	constexpr MInt &operator+=(MInt rhs) & {
		x = norm(x + rhs.x);
		return *this;
	}
	constexpr MInt &operator-=(MInt rhs) & {
		x = norm(x - rhs.x);
		return *this;
	}
	constexpr MInt &operator/=(MInt rhs) & {
		return *this *= rhs.inv();
	}
	friend constexpr MInt operator*(MInt lhs, MInt rhs) {
		MInt res = lhs;
		res *= rhs;
		return res;
	}
	friend constexpr MInt operator+(MInt lhs, MInt rhs) {
		MInt res = lhs;
		res += rhs;
		return res;
	}
	friend constexpr MInt operator-(MInt lhs, MInt rhs) {
		MInt res = lhs;
		res -= rhs;
		return res;
	}
	friend constexpr MInt operator/(MInt lhs, MInt rhs) {
		MInt res = lhs;
		res /= rhs;
		return res;
	}
	friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
		i64 v;
		is >> v;
		a = MInt(v);
		return is;
	}
	friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) {
		return os << a.val();
	}
	friend constexpr bool operator==(MInt lhs, MInt rhs) {
		return lhs.val() == rhs.val();
	}
	friend constexpr bool operator!=(MInt lhs, MInt rhs) {
		return lhs.val() != rhs.val();
	}
};

template<>
int MInt<0>::Mod = 1;

template<int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();

constexpr int P = 1E9 + 7;
using Z = MInt<P>;

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

	std::vector adj(n + 1, std::vector<int>());
	for (int i = 1; i <= n - 1; i += 1) {
		int u, v;
		std::cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	std::vector dp(n + 1, std::vector<Z>(2));

	auto dfs = [&](auto && self, int u, int par)->void {
		dp[u][0] = dp[u][1] = 1;
		for (const auto & v : adj[u]) {
			if (v == par) {
				continue;
			}
			self(self, v, u);
			dp[u][0] *= (dp[v][0] + dp[v][1]);
			dp[u][1] *= dp[v][0];
		}
	};
	dfs(dfs, 1, 0);

	std::cout << (dp[1][0] + dp[1][1]) << "\n";
	return 0;
}
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

constexpr int $N = 277777777;
constexpr int $M = 998244353;
using X = MInt < $N >;
using Y = MInt < $M >;
using Z = MInt<1000000007>;
constexpr int M = 1E6;

constexpr X BASE1 = 131;
constexpr Y BASE2 = 77;

struct B {
	std::vector<X>P;
	std::vector<Y>p;
	B() {}
	B(int n) {
		P.resize(n + 1), p.resize(n + 1);
		P[0] = 1;
		p[0] = 1;
		for (int i = 1; i <= n; i += 1) {
			P[i] = P[i - 1] * BASE1;
			p[i] = p[i - 1] * BASE2;
		}
	}
} BASE(M);

struct Hash {
	std::vector<X>H;
	std::vector<Y>h;
	Hash() {}
	Hash(const std::string& s) {
		int n = s.size();
		H.resize(n + 1), h.resize(n + 1);
		for (int i = 1; i <= n; i += 1) {
			H[i] = H[i - 1] * BASE1 + (X)((int)s[i - 1]);
			h[i] = h[i - 1] * BASE2 + (Y)((int)s[i - 1]);
		}
	}
	std::pair<X, Y> Query(int l, int r) {
		X a = H[r] - H[l - 1] * BASE.P[r - l + 1];
		Y b = h[r] - h[l - 1] * BASE.p[r - l + 1];
		return std::pair(a, b);
	}
};

Z cal(const std::string & s) {
	int n = s.size();
	std::vector dp(n, std::vector<Z>(26));
	for (int i = 0; i < n; i += 1) {
		Z sum = 1;
		for (int j = 0; j <= 25; j += 1) {
			if (i) {
				dp[i][j] = dp[i - 1][j];
			}
			sum += dp[i][j];
		}
		dp[i][s[i] - 'a'] = sum;
	}
	return std::accumulate(dp.back().begin(), dp.back().end(), Z(0));
}

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, m;
	std::cin >> n >> m;

	std::string s, t;
	std::cin >> s >> t;

	int l = -1, r = -1;

	std::vector<int>f(n), g(n);
	for (int i = 0, j = 0; i < n and j < m; i += 1) {
		if (i) {
			f[i] = f[i - 1];
		}
		if (s[i] == t[j]) {
			f[i] = j++;
			if (j == m) {
				l = i;
			}
		}
	}

	int limit = 0;
	for (int i = n - 1, j = 0; i >= 0 and j < m; i -= 1) {
		if (s[i] == t[j]) {
			g[i] = j++;
			if (j == m) {
				r = i;
				limit = m - f[i];
			}
		}
	}

	if (l == -1 or r == -1) {
		std::cout << 0 << "\n";
		return 0;
	}

	Z ans = 0;

	Hash pref(t);
	Hash surf(std::string(t.rbegin(), t.rend()));
	for (int i = limit; i <= m; i += 1) {
		if (pref.Query(m - i + 1, m) == surf.Query(1, i)) {
			ans += 1;
		}
	}

	if (l + 1 < r) {
		ans += cal(s.substr(l + 1, r - l + 1));
	}

	std::cout << ans << "\n";

	return 0;
}
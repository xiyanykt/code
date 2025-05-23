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

namespace atcoder {

namespace internal {

constexpr long long safe_mod(long long x, long long m) {
	x %= m;
	if (x < 0) x += m;
	return x;
}

struct barrett {
	unsigned int _m;
	unsigned long long im;

	explicit barrett(unsigned int m) : _m(m), im((unsigned long long)(-1) / m + 1) {}

	unsigned int umod() const { return _m; }

	unsigned int mul(unsigned int a, unsigned int b) const {
		unsigned long long z = a;
		z *= b;
#ifdef _MSC_VER
		unsigned long long x;
		_umul128(z, im, &x);
#else
		unsigned long long x =
		    (unsigned long long)(((unsigned __int128)(z) * im) >> 64);
#endif
		unsigned long long y = x * _m;
		return (unsigned int)(z - y + (z < y ? _m : 0));
	}
};

constexpr long long pow_mod_constexpr(long long x, long long n, int m) {
	if (m == 1) return 0;
	unsigned int _m = (unsigned int)(m);
	unsigned long long r = 1;
	unsigned long long y = safe_mod(x, m);
	while (n) {
		if (n & 1) r = (r * y) % _m;
		y = (y * y) % _m;
		n >>= 1;
	}
	return r;
}

constexpr bool is_prime_constexpr(int n) {
	if (n <= 1) return false;
	if (n == 2 || n == 7 || n == 61) return true;
	if (n % 2 == 0) return false;
	long long d = n - 1;
	while (d % 2 == 0) d /= 2;
	constexpr long long bases[3] = {2, 7, 61};
	for (long long a : bases) {
		long long t = d;
		long long y = pow_mod_constexpr(a, t, n);
		while (t != n - 1 && y != 1 && y != n - 1) {
			y = y * y % n;
			t <<= 1;
		}
		if (y != n - 1 && t % 2 == 0) {
			return false;
		}
	}
	return true;
}
template <int n>
constexpr bool is_prime = is_prime_constexpr(n);

constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
	a = safe_mod(a, b);
	if (a == 0) return {b, 0};

	long long s = b, t = a;
	long long m0 = 0, m1 = 1;

	while (t) {
		long long u = s / t;
		s -= t * u;
		m0 -= m1 * u;  // |m1 * u| <= |m1| * s <= b

		auto tmp = s;
		s = t;
		t = tmp;
		tmp = m0;
		m0 = m1;
		m1 = tmp;
	}
	if (m0 < 0) m0 += b / s;
	return {s, m0};
}

constexpr int primitive_root_constexpr(int m) {
	if (m == 2) return 1;
	if (m == 167772161) return 3;
	if (m == 469762049) return 3;
	if (m == 754974721) return 11;
	if (m == 998244353) return 3;
	int divs[20] = {};
	divs[0] = 2;
	int cnt = 1;
	int x = (m - 1) / 2;
	while (x % 2 == 0) x /= 2;
	for (int i = 3; (long long)(i)*i <= x; i += 2) {
		if (x % i == 0) {
			divs[cnt++] = i;
			while (x % i == 0) {
				x /= i;
			}
		}
	}
	if (x > 1) {
		divs[cnt++] = x;
	}
	for (int g = 2;; g++) {
		bool ok = true;
		for (int i = 0; i < cnt; i++) {
			if (pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {
				ok = false;
				break;
			}
		}
		if (ok) return g;
	}
}
template <int m>
constexpr int primitive_root = primitive_root_constexpr(m);

unsigned long long floor_sum_unsigned(unsigned long long n,
                                      unsigned long long m,
                                      unsigned long long a,
                                      unsigned long long b) {
	unsigned long long ans = 0;
	while (true) {
		if (a >= m) {
			ans += n * (n - 1) / 2 * (a / m);
			a %= m;
		}
		if (b >= m) {
			ans += n * (b / m);
			b %= m;
		}

		unsigned long long y_max = a * n + b;
		if (y_max < m) break;
		n = (unsigned long long)(y_max / m);
		b = (unsigned long long)(y_max % m);
		std::swap(m, a);
	}
	return ans;
}

}  // namespace internal

}  // namespace atcoder

namespace atcoder {

namespace internal {

#ifndef _MSC_VER
template <class T>
using is_signed_int128 =
    typename std::conditional < std::is_same<T, __int128_t>::value ||
    std::is_same<T, __int128>::value,
    std::true_type,
    std::false_type >::type;

template <class T>
using is_unsigned_int128 =
    typename std::conditional < std::is_same<T, __uint128_t>::value ||
    std::is_same<T, unsigned __int128>::value,
    std::true_type,
    std::false_type >::type;

template <class T>
using make_unsigned_int128 =
    typename std::conditional<std::is_same<T, __int128_t>::value,
    __uint128_t,
    unsigned __int128>;

template <class T>
using is_integral = typename std::conditional < std::is_integral<T>::value ||
                    is_signed_int128<T>::value ||
                    is_unsigned_int128<T>::value,
                    std::true_type,
                    std::false_type >::type;

template <class T>
using is_signed_int = typename std::conditional < (is_integral<T>::value &&
                      std::is_signed<T>::value) ||
                      is_signed_int128<T>::value,
                      std::true_type,
                      std::false_type >::type;

template <class T>
using is_unsigned_int =
    typename std::conditional < (is_integral<T>::value &&
                                 std::is_unsigned<T>::value) ||
    is_unsigned_int128<T>::value,
    std::true_type,
    std::false_type >::type;

template <class T>
using to_unsigned = typename std::conditional <
                    is_signed_int128<T>::value,
                    make_unsigned_int128<T>,
                    typename std::conditional<std::is_signed<T>::value,
                    std::make_unsigned<T>,
                    std::common_type<T>>::type >::type;

#else

template <class T>
using is_integral = typename std::is_integral<T>;

template <class T>
using is_signed_int =
    typename std::conditional < is_integral<T>::value && std::is_signed<T>::value,
    std::true_type,
    std::false_type >::type;

template <class T>
using is_unsigned_int =
    typename std::conditional < is_integral<T>::value &&
    std::is_unsigned<T>::value,
    std::true_type,
    std::false_type >::type;

template <class T>
using to_unsigned = typename std::conditional<is_signed_int<T>::value,
      std::make_unsigned<T>,
      std::common_type<T>>::type;

#endif

template <class T>
using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;

template <class T>
using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;

template <class T>
using to_unsigned_t = typename to_unsigned<T>::type;

}  // namespace internal

}  // namespace atcoder

namespace atcoder {

namespace internal {

struct modint_base {};
struct static_modint_base : modint_base {};

template <class T>
using is_modint = std::is_base_of<modint_base, T>;
template <class T>
using is_modint_t = std::enable_if_t<is_modint<T>::value>;

}  // namespace internal

template < int m, std::enable_if_t<(1 <= m)>* = nullptr>
           struct static_modint : internal::static_modint_base {
               using mint = static_modint;

               public:
static constexpr int mod() { return m; }
static mint raw(int v) {
	mint x;
	x._v = v;
	return x;
}

static_modint() : _v(0) {}
template <class T, internal::is_signed_int_t<T>* = nullptr>
static_modint(T v) {
	long long x = (long long)(v % (long long)(umod()));
	if (x < 0) x += umod();
	_v = (unsigned int)(x);
}
template <class T, internal::is_unsigned_int_t<T>* = nullptr>
static_modint(T v) {
	_v = (unsigned int)(v % umod());
}

unsigned int val() const { return _v; }

mint& operator++() {
	_v++;
	if (_v == umod()) _v = 0;
	return *this;
}
mint& operator--() {
	if (_v == 0) _v = umod();
	_v--;
	return *this;
}
mint operator++(int) {
	mint result = *this;
	++*this;
	return result;
}
mint operator--(int) {
	mint result = *this;
	--*this;
	return result;
}

mint& operator+=(const mint& rhs) {
	_v += rhs._v;
	if (_v >= umod()) _v -= umod();
	return *this;
}
mint& operator-=(const mint& rhs) {
	_v -= rhs._v;
	if (_v >= umod()) _v += umod();
	return *this;
}
mint& operator*=(const mint& rhs) {
	unsigned long long z = _v;
	z *= rhs._v;
	_v = (unsigned int)(z % umod());
	return *this;
}
mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }

mint operator+() const { return *this; }
mint operator-() const { return mint() - *this; }

mint pow(long long n) const {
	assert(0 <= n);
	mint x = *this, r = 1;
	while (n) {
		if (n & 1) r *= x;
		x *= x;
		n >>= 1;
	}
	return r;
}
mint inv() const {
	if (prime) {
		assert(_v);
		return pow(umod() - 2);
	} else {
		auto eg = internal::inv_gcd(_v, m);
		assert(eg.first == 1);
		return eg.second;
	}
}

friend mint operator+(const mint& lhs, const mint& rhs) {
	return mint(lhs) += rhs;
}
friend mint operator-(const mint& lhs, const mint& rhs) {
	return mint(lhs) -= rhs;
}
friend mint operator*(const mint& lhs, const mint& rhs) {
	return mint(lhs) *= rhs;
}
friend mint operator/(const mint& lhs, const mint& rhs) {
	return mint(lhs) /= rhs;
}
friend bool operator==(const mint& lhs, const mint& rhs) {
	return lhs._v == rhs._v;
}
friend bool operator!=(const mint& lhs, const mint& rhs) {
	return lhs._v != rhs._v;
}

private:
unsigned int _v;
static constexpr unsigned int umod() { return m; }
static constexpr bool prime = internal::is_prime<m>;
                                                };

template <int id>
struct dynamic_modint : internal::modint_base {
    using mint = dynamic_modint;

    public:
static int mod() { return (int)(bt.umod()); }
static void set_mod(int m) {
	assert(1 <= m);
	bt = internal::barrett(m);
}
static mint raw(int v) {
	mint x;
	x._v = v;
	return x;
}

dynamic_modint() : _v(0) {}
template <class T, internal::is_signed_int_t<T>* = nullptr>
dynamic_modint(T v) {
	long long x = (long long)(v % (long long)(mod()));
	if (x < 0) x += mod();
	_v = (unsigned int)(x);
}
template <class T, internal::is_unsigned_int_t<T>* = nullptr>
dynamic_modint(T v) {
	_v = (unsigned int)(v % mod());
}

unsigned int val() const { return _v; }

mint& operator++() {
	_v++;
	if (_v == umod()) _v = 0;
	return *this;
}
mint& operator--() {
	if (_v == 0) _v = umod();
	_v--;
	return *this;
}
mint operator++(int) {
	mint result = *this;
	++*this;
	return result;
}
mint operator--(int) {
	mint result = *this;
	--*this;
	return result;
}

mint& operator+=(const mint& rhs) {
	_v += rhs._v;
	if (_v >= umod()) _v -= umod();
	return *this;
}
mint& operator-=(const mint& rhs) {
	_v += mod() - rhs._v;
	if (_v >= umod()) _v -= umod();
	return *this;
}
mint& operator*=(const mint& rhs) {
	_v = bt.mul(_v, rhs._v);
	return *this;
}
mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }

mint operator+() const { return *this; }
mint operator-() const { return mint() - *this; }

mint pow(long long n) const {
	assert(0 <= n);
	mint x = *this, r = 1;
	while (n) {
		if (n & 1) r *= x;
		x *= x;
		n >>= 1;
	}
	return r;
}
mint inv() const {
	auto eg = internal::inv_gcd(_v, mod());
	assert(eg.first == 1);
	return eg.second;
}

friend mint operator+(const mint& lhs, const mint& rhs) {
	return mint(lhs) += rhs;
}
friend mint operator-(const mint& lhs, const mint& rhs) {
	return mint(lhs) -= rhs;
}
friend mint operator*(const mint& lhs, const mint& rhs) {
	return mint(lhs) *= rhs;
}
friend mint operator/(const mint& lhs, const mint& rhs) {
	return mint(lhs) /= rhs;
}
friend bool operator==(const mint& lhs, const mint& rhs) {
	return lhs._v == rhs._v;
}
friend bool operator!=(const mint& lhs, const mint& rhs) {
	return lhs._v != rhs._v;
}

private:
unsigned int _v;
static internal::barrett bt;
static unsigned int umod() { return bt.umod(); }
      };
template <int id>
internal::barrett dynamic_modint<id>::bt(998244353);

using modint998244353 = static_modint<998244353>;
using modint1000000007 = static_modint<1000000007>;
using modint = dynamic_modint < -1 >;

namespace internal {

    template <class T>
    using is_static_modint = std::is_base_of<internal::static_modint_base, T>;

    template <class T>
    using is_static_modint_t = std::enable_if_t<is_static_modint<T>::value>;

    template <class>
    struct is_dynamic_modint : public std::false_type {};
    template <int id>
    struct is_dynamic_modint<dynamic_modint<id>> : public std::true_type {};

    template <class T>
    using is_dynamic_modint_t = std::enable_if_t<is_dynamic_modint<T>::value>;

                                                                  }  // namespace internal

}  // namespace atcoder

using Z = atcoder::static_modint<998244353>;
using F = atcoder::static_modint < int(1E9) + 7 >;
const Z Dis1 = 127;
const F Dis2 = 133;
constexpr int KN = 3E5;
Z pw1[KN + 1];
F pw2[KN + 1];

struct Hash {
	std::vector<Z>h1;
	std::vector<F>h2;

	Hash() {}
	Hash(const std::string& s) {
		int n = s.size();
		h1.resize(n + 1);
		h2.resize(n + 1);
		for (int i = 1; i <= n; i += 1) {
			h1[i] = h1[i - 1] * Dis1 + int(s[i - 1]);
			h2[i] = h2[i - 1] * Dis2 + int(s[i - 1]);
		}
	}

	std::pair<Z, F> getRange(int l, int r) {
		Z a = h1[r] - h1[l - 1] * pw1[r - l + 1];
		F b = h2[r] - h2[l - 1] * pw2[r - l + 1];
		return std::pair(a, b);
	}
};

struct AhoCorasick {
	static constexpr int ALPHABET = 26;

	struct Node {
	    int len;
	    int link;
	    std::array<int, ALPHABET> next;
	Node() : len{0}, link{0}, next{} {}
	              };

	std::vector<Node> t;

	AhoCorasick() {
		t.assign(2, Node());
		t[0].next.fill(1);
		t[0].len = -1;
	}

	int newNode() {
		t.emplace_back();
		return t.size() - 1;
	}

	int add(const std::string &a) {
		int p = 1;
		for (auto c : a) {
			int x = c - 'a';
			if (t[p].next[x] == 0) {
				t[p].next[x] = newNode();
				t[t[p].next[x]].len = t[p].len + 1;
			}
			p = t[p].next[x];
		}
		return p;
	}

	void work() {
		std::queue<int> q;
		q.push(1);
		while (!q.empty()) {
			int x = q.front();
			q.pop();
			for (int i = 0; i < ALPHABET; i++) {
				if (t[x].next[i] == 0) {
					t[x].next[i] = t[t[x].link].next[i];
				} else {
					t[t[x].next[i]].link = t[t[x].link].next[i];
					q.push(t[x].next[i]);
				}
			}
		}
	}

	int next(int p, int x) {
		return t[p].next[x];
	}

	int link(int p) {
		return t[p].link;
	}

	int len(int p) {
		return t[p].len;
	}

	int size() {
		return t.size();
	}
};

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout << std::fixed << std::setprecision(13);

	pw1[0] = 1;
	pw2[0] = 1;
	for (int i = 1; i <= KN; i += 1) {
		pw1[i] = pw1[i - 1] * Dis1;
		pw2[i] = pw2[i - 1] * Dis2;
	}

	auto solve = [&]() {
		int n;
		std::string A, C;
		std::cin >> n >> A >> C;

		Hash hc(C);
		AhoCorasick ac;
		std::vector<int>end(n + 1, -1);
		for (int i = 1; i <= n; i += 1) {
			std::string t, s;
			std::cin >> t >> s;
			if (std::ssize(s) >= std::ssize(C)) {
				Hash hs(s);
				int ok = 0;
				for (int i = std::ssize(C); i <= std::ssize(s) and ok == 0; i += 1) {
					if (hs.getRange(i - std::ssize(C) + 1, i) == hc.getRange(1, std::ssize(C))) {
						ok = 1;
					}
				}
				if (ok) {
					end[i] = ac.add(t);
				}
			}
		}

		ac.work();
		std::vector<int>f(ac.size());
		int p = 1;
		for (const auto & c : A) {
			p = ac.next(p, c - 'a');
			f[p] += 1;
		}

		std::vector<std::vector<int>>adj(ac.size());
		for (int i = 2; i < ac.size(); i += 1) {
			adj[ac.link(i)].push_back(i);
		}

		auto dfs = [&](auto && dfs, int u) ->void {
			for (const auto & v : adj[u]) {
				dfs(dfs, v);
				f[u] += f[v];
			}
		};
		dfs(dfs, 1);

		for (int i = 1; i <= n; i += 1) {
			if (end[i] != -1 and f[end[i]] >= 1) {
				std::cout << i << ' ';
			}
		}
		std::cout << '\n';
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}

	return 0;
}
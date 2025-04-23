#include<bits/stdc++.h>

using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128;
using f128 = __float128;

template<typename T>
struct Fenwick {
	int n;
	std::vector<T>a;

	constexpr Fenwick(int n): n(n), a(n + 1, T()) {}

	void add(int p, const T& x) {
		for (int i = p; i <= n; i += i & -i) {
			a[i] += x;
		}
	}

	T sum(int p) {
		T ans = T();
		for (int i = p; i > 0; i -= i & -i) {
			ans += a[i];
		}
		return ans;
	}

	T getRange(int l, int r) {
		return sum(r) - sum(l - 1);
	}

	int select(int k) {
		int x = 0;
		T cur = T();
		for (int i = std::__lg(n); ~i; i -= 1) {
			x += 1 << i;
			if (x >= n or cur + a[x] >= k) {
				x -= 1 << i;
			} else {
				cur = cur + a[x];
			}
		}
		return x + 1;
	}
};

constexpr int Mod = 1 << 21;

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout << std::fixed << std::setprecision(13);

	constexpr int S = 21;
	int q;
	std::cin >> q;

	std::vector fen(S, Fenwick<int>(Mod));
	std::vector<int>tag(S);
	std::vector<int>stk;

	auto del = [&]() ->void {
		int x = stk.back();
		stk.pop_back();
		for (int i = 0; i < S; i += 1) {
			const int P = 1 << i + 1;
			int pos = (x - tag[i] % P + P) % P;
			fen[i].add(pos + 1, -1);
			tag[i] -= x % P;
			tag[i] += P;
			tag[i] %= P;
		}
	};

	auto add = [&](int v) {
		for (int i = 0; i < S; i += 1) {
			const int P = 1 << i + 1;
			tag[i] += v % P;
			tag[i] %= P;
			int pos = (v - tag[i] % P + P) % P;
			fen[i].add(pos + 1, 1);
		}
		stk.push_back(v);
	};

	auto cal = [&]() ->int {
		int res = 0;
		for (int i = 0; i < S; i += 1) {
			int lo = 1 << i, hi = (1 << i + 1) - 1;
			const int P = 1 << i + 1;
			int l = (lo - tag[i] % P + P) % P;
			int r = (hi - tag[i] % P + P) % P;
			int c;
			if (l <= r) {
				c = fen[i].getRange(l + 1, r + 1);
			} else {
				c = fen[i].getRange(l + 1, hi + 1) + fen[i].getRange(1, r + 1);
			}
			if (c & 1) {
				res |= 1 << i;
			}
		}
		return res;
	};

	while (q--) {
		int t, v;
		std::cin >> t >> v;
		while (t--) {
			del();
		}
		add(v);
		std::cout << (cal()) << '\n';
	}

	return 0;
}
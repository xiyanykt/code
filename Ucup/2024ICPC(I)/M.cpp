#include<bits/stdc++.h>

using i64 = int64_t;

template <class T>
struct Fenwick {
	int n;
	std::vector<T>a;

	Fenwick(int n) {
		this->n = n;
		a.assign(n + 1, T());
	}

	void add(int p, const T& x) {
		for (int i = p; i <= n; i += i & -i) {
			a[i] += x;
		}
	}

	T sum(int p) {
		T res = T{0};
		for (int i = p; i >= 1; i -= 1) {
			res += a[i];
		}
		return res;
	}

	T getRange(int l, int r) {
		return sum(r) - sum(l - 1);
	}
};

constexpr int Mod = 998244353;

constexpr int add(int a, int b) {
	return (i64(a) + b) % Mod;
}

constexpr int mul(int a, int b) {
	return (i64(a) * b) % Mod;
}

constexpr int power(int a, int b) {
	int res = 1;
	for (; b != 0; b >>= 1, a = mul(a, a)) {
		if (b & 1) {
			res = mul(res, a);
		}
	}
	return res;
}

constexpr int inv(int a) {
	return power(a, Mod - 2);
}

void solve() {
	int n;
	std::cin >> n;

	std::vector<std::map<std::string, int>>rec(100);
	std::map<char, int>cnt;
	for (int i = 1; i <= n; i += 1) {
		std::string s;
		char x;
		std::string op;
		std::cin >> s >> x >> op;
		if (op[0] == 'a') {
			if (not rec[x - 'A'].count(s)) {
				cnt[x] += 1;
			}
			rec[x - 'A'][s] += 1;
		}
	}

	char ans = '#';
	for (const auto & [x, v] : cnt) {
		if (v > cnt[ans]) {
			ans = x;
		}
	}

	std::cout << ans << '\n';
}

auto main() ->int32_t{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...) void(0)
#endif

constexpr i64 mod = 998244353;
i64 power(i64 a, i64 r) {
	i64 res = 1;
	for (; r; r >>= 1, a = a * a % mod)
		if (r & 1) res = res * a % mod;
	return res;
}
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int t;
	cin >> t;
	for (int ti = 0; ti < t; ti += 1) {
		int n;
		cin >> n;
		vector<int> a(n);
		for (int& ai : a) cin >> ai;
		int ans = 0;
		auto check = [&](int i, int j) {
			if (a[j] <= 0) return i >= -a[i];
			if (a[i] >= 0) return n - j - 1 >= a[j];
			if (i >= -a[i] and n - j - 1 >= a[j] - a[i]) return true;
			return n - j - 1 >= a[j] and i >= a[j] - a[i];
		};
		for (int i = 0; i < n; i += 1) {
			int l = i - 1, r = n - 1;
			while (r > l) {
				int m = (l + r + 1) / 2;
				if (check(i, m)) {
					l = m;
				} else {
					r = m - 1;
				}
			}
			ans = max(ans, l - i + 1);
		}
		cout << ans << "\n";
	}
}
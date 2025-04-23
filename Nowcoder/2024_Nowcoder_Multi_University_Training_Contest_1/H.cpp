#include<bits/stdc++.h>

using i64 = int64_t;

const std::string I = "lzr010506";

#define int long long

signed main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n;
	std::cin >> n;

	std::map<std::string, std::pair<int, int>>l;
	for (int i = 0; i < n; i += 1) {
		std::string s;
		std::cin >> s;
		int x, y;
		std::cin >> x >> y;
		l[s] = { -x, y};
	}

	int m;
	std::cin >> m;

	std::map<std::string, std::pair<int, int>>r;
	for (int i = 0; i < m; i += 1) {
		std::string s;
		std::cin >> s;
		int x, y;
		std::cin >> x >> y;
		r[s] = { -x, y};
	}

	std::multiset<std::pair<int, int>>a, b;

	auto u = l[I], v = r[I];

	l.erase(I), r.erase(I);

	for (const auto & [x, z] : l) {
		if (not r.count(x)) {
			a.insert(z);
		}
	}
	for (const auto & [x, z] : r) {
		if (not l.count(x)) {
			b.insert(z);
		}
	}

	a.insert(u);

	b.insert(v);

	int ans = 1E9;
	int j = 1;
	for (const auto & c : a) {
		if (c == u) {
			ans = std::min(ans, j);
		} else {
			j += 1;
		}
	}
	j = 1;
	for (const auto & c : b) {
		if (c == v) {
			ans = std::min(ans, j);
		} else {
			j += 1;
		}
	}

	std::cout << ans << "\n";

	return 0;
}
#include<bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f64 = long double;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

template<class T>
constexpr bool chmax(T& x, T y) {
	if (y > x) {
		x = y;
		return true;
	}
	return false;
}

template<class T>
constexpr bool chmin(T& x, T y) {
	if (y < x) {
		x = y;
		return true;
	}
	return false;
}

constexpr int Kn = 2E5;
std::vector<int>adj[Kn + 1];
int ca[2 * Kn + 1], cb[2 * Kn + 1];

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	for (int x = 1; x <= Kn; x += 1) {
		for (int y = x; y <= Kn; y += x) {
			adj[y].push_back(x);
		}
	}

	int n, m, q;
	std::cin >> n >> m >> q;

	std::vector<int>a(n + 1), b(m + 1);
	for (int i = 1; i <= n; i += 1) {
		std::cin >> a[i];
	}
	for (int i = 1; i <= m; i += 1) {
		std::cin >> b[i];
	}

	i64 sa = std::accumulate(a.begin() + 1, a.end(), 0LL);
	i64 sb = std::accumulate(b.begin() + 1, b.end(), 0LL);

	for (int i = 1; i <= n; i += 1) {
		int x = sa - a[i];
		if (x >= -Kn && x <= Kn) {
			ca[x + Kn] += 1;
		}
	}
	for (int i = 1; i <= m; i += 1) {
		int y = sb - b[i];
		if (y >= -Kn && y <= Kn) {
			cb[y + Kn] += 1;
		}
	}

	auto ok = [&](int x, int y) {
		if ((ca[Kn + x] && cb[Kn + y]) || (ca[Kn + y] && cb[Kn + x])) {
			return true;
		}
		return false;
	};

	while (q--) {
		int x;
		std::cin >> x;
		if (std::ranges::any_of(adj[std::abs(x)], [&](const auto & u) {
		return ok(u, x / u) || ok(-u, -(x / u));
		})) {
			std::cout << "YES\n";
		} else {
			std::cout << "NO\n";
		}
	}

	return 0;
}
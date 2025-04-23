#include<bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f64 = long double;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

#ifndef ONLINE_JUDGE
#include "algo/debug.hpp"
#else
#define debug(...) (void)42
#endif

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

static constexpr int dx[] = {0, 0, 1, -1};
static constexpr int dy[] = {1, -1, 0, 0};

struct Node {
	int x, y;
	i64 val;

	Node () {
		x = 0;
		y = 0;
		val = 0;
	}

	Node(const int & x, const int & y, const i64& val): x(x), y(y), val(val) {}

	constexpr friend bool operator<(const Node& a, const Node& b) {
		return a.val < b.val;
	}
};

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, m, w;
	std::cin >> n >> m >> w;

	int a, b;
	std::cin >> a >> b;

	std::vector<std::vector<i64>>s(n + 1, std::vector<i64>(m + 1));
	for (int i = 1; i <= n; i += 1) {
		for (int j = 1; j <= m; j += 1) {
			std::cin >> s[i][j];
		}
	}

	auto ok = [&](int i, int j) {
		return (i >= 1 && i <= n && j >= 1 && j <= m);
	};

	constexpr i64 inf = 1E18;
	std::vector<std::vector<bool>>vis(n + 1, std::vector<bool>(m + 1));
	std::priority_queue<std::tuple<i64, int, int>, std::vector<std::tuple<i64, int, int>>, std::greater<>>q;

	i64 cur = s[a][b];
	q.push({0, a, b});
	vis[a][b] = true;
	while (!q.empty()) {
		auto [v, x, y] = q.top();
		q.pop();
		if (i128(v) * w >= cur) {
			break;
		}
		cur += v;
		for (int k = 0; k < 4; k += 1) {
			int nx = x + dx[k], ny = y + dy[k];
			if (ok(nx, ny) && !vis[nx][ny]) {
				vis[nx][ny] = true;
				q.push({s[nx][ny], nx, ny});
			}
		}
	}

	std::cout << cur << '\n';
	return 0;
}
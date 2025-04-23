#include<bits/stdc++.h>

using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;
using i128 = __int128_t;
using f128 = __float128;

#ifndef ONLINE_JUDGE
#include "algo\debug.hpp"
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

struct PresidentTree {

	struct Node {
		int ls, rs, val;
	};

	int n;
	int cnt;
	std::vector<Node>info;

	PresidentTree() {}
	PresidentTree(int n) {
		this->n = n;
		cnt = 0;
		info.resize(n << 5);
	}

	void push(int p) {
		info[p].val = info[info[p].ls].val + info[info[p].rs].val;
	}

	//root root [V] x
	void update(int& now, int pre, int l, int r, int pos) {
		info[now = ++cnt] = info[pre];
		if (l == r) {
			info[now].val += 1;
			return;
		}
		int mid = std::midpoint(l, r);
		if (pos <= mid) {
			update(info[now].ls, info[pre].ls, l, mid, pos);
		} else {
			update(info[now].rs, info[pre].rs, mid + 1, r, pos);
		}
		push(now);
	}

	//root root [V] [L,R]
	int getRange(int k, int p, int l, int r, int L, int R) {
		if (l > R or r < L) {
			return 0;
		}
		if (L <= l and r <= R) {
			return info[p].val - info[k].val;
		}
		int mid = std::midpoint(l, r);
		return getRange(info[k].ls, info[p].ls, l, mid, L, R) + getRange(info[k].rs, info[p].rs, mid + 1, r, L, R);
	}

	//root root kth [V]
	int getKthMax(int l, int r, int k, int L, int R) {
		if (info[r].val - info[l].val < k) {
			return 0;
		}
		if (L == R) {
			return L;
		}
		int mid = std::midpoint(L, R);
		int x = info[info[r].rs].val - info[info[l].rs].val;
		return k <= x ? getKthMax(info[l].rs, info[r].rs, k, mid + 1, R) : getKthMax(info[l].ls, info[r].ls, k - x, L, mid);
	}

	//root root kth [V]
	int getKthMin(int l, int r, int k, int L, int R) {
		if (info[r].val - info[l].val < k) {
			return 0;
		}
		if (L == R) {
			return L;
		}
		int mid = std::midpoint(L, R);
		int x = info[info[r].ls].val - info[info[l].ls].val;
		return k <= x ? getKthMin(info[l].ls, info[r].ls, k, L, mid) : getKthMin(info[l].rs, info[r].rs, k - x, mid + 1, R);
	}
};

constexpr int inf = 1E9;
constexpr int KN = 1 << 20;

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout << std::fixed << std::setprecision(13);
	int n;
	std::cin >> n;

	std::vector<int>a(n + 1);
	for (int i = 1; i <= n; i += 1) {
		std::cin >> a[i];
	}

	std::vector<int>t(n + 1);
	PresidentTree pst(KN);
	for (int i = 1; i <= n; i += 1) {
		pst.update(t[i], t[i - 1], 1, inf, a[i]);
	}

	auto getRange = [&](int l, int r) {
		int k = r - l + 1;
		return pst.getKthMin(t[l - 1], t[r], (k + 1) / 2, 1, inf);
	};

	std::vector b(n + 1, std::vector<int>(n + 1));
	for (int l = 1; l <= n; l += 1) {
		for (int r = l; r <= n; r += 1) {
			b[l][r] = getRange(l, r);
		}
	}

	// for (int l = 1; l <= n; l += 1) {
	//     for (int r = 1; r <= n; r += 1) {
	//         std::cout << b[l][r] << " \n"[r == n];
	//     }
	// }

	auto check = [&](int x) {
		std::vector c(n + 1, std::vector<int>(n + 1));
		for (int l = 1; l <= n; l += 1) {
			for (int r = l; r <= n; r += 1) {
				c[l][r] = b[l][r] >= x ? 1 : 0;
			}
		}

		for (int i = 1; i <= n; i += 1) {
			for (int j = 1; j <= n; j += 1) {
				c[i][j] += c[i - 1][j] + c[i][j - 1] - c[i - 1][j - 1];
			}
		}

		auto ok = [&](int l, int r) {
			return ((r - l + 1) * (r - l + 2) / 2);
		};

		auto getMatrix = [&](int x1, int y1, int x2, int y2) {
			return c[x1][y1] + c[x2 - 1][y2 - 1] - c[x2 - 1][y1] - c[x1][y2 - 1];
		};

		int all = n * (n + 1) / 2, cnt = 0;
		for (int l = 1; l <= n; l += 1) {
			for (int r = l; r <= n; r += 1) {
				if (ok(l, r) < 2 * getMatrix(r, r, l, l)) {
					cnt += 1;
				}
			}
		}
		return 2 * cnt > all;
	};

	int lo = 1, hi = inf;
	while (lo <= hi) {
		int mid = (lo + hi) >> 1;
		if (check(mid)) {
			lo = mid + 1;
		} else {
			hi = mid - 1;
		}
	}

	std::cout << lo - 1 << '\n';

	return 0;
}
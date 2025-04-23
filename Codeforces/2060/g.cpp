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

template<typename T>
struct Fenwick {
	int n;
	std::vector<T>a;

	Fenwick() {

	}
	
	Fenwick(int n) {
		this->n = n;
		a.assign(n + 1, T());
	}

	void add(int p, const T& x) {
		if (p >= 1 && p <= n) {
			for (int i = p; i <= n; i += i & -i) {
				a[i] += x;
			}
		}
	}

	T sum(int p) {
		T ans = T();
		if (p >= 1 && p <= n) {
			for (int i = p; i > 0; i -= i & -i) {
				ans += a[i];
			}
		}
		return ans;
	}

	T rangeQuery(int l, int r) {
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

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto solve = [&]() {
        int n;
        std::cin >> n;

        std::vector<std::pair<int, int>>p(n);
        for (auto & [x, y] : p) {
            std::cin >> x;
        }
        for (auto & [x, y] : p) {
            std::cin >> y;
        }

        std::ranges::sort(p, {}, [&](const auto & u) {
            const auto & [x, y] = u;
            return std::min(x, y);
        });

        Fenwick<int>fen(2 * n + 2);
        i64 cnt1 = 0;
        for (auto & [x, y] : p) {
            cnt1 += fen.rangeQuery(x + 1, 2 * n + 1);
            fen.add(x, 1);
        }

        fen = Fenwick<int>(2 * n + 2);
        i64 cnt2 = 0;
        for (auto & [y, x] : p) {
            cnt1 += fen.rangeQuery(x + 1, 2 * n + 1);
            fen.add(x, 1);
        }

        debug(cnt1, cnt2);
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
